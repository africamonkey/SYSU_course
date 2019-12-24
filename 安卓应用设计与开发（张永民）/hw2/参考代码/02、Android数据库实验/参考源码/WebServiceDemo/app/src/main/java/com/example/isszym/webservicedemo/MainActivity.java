package com.example.isszym.webservicedemo;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.ksoap2.SoapEnvelope;
import org.ksoap2.serialization.SoapObject;
import org.ksoap2.serialization.SoapPrimitive;
import org.ksoap2.serialization.SoapSerializationEnvelope;
import org.ksoap2.transport.HttpTransportSE;
import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLConnection;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private EditText edit_param;
//    private Button btn_attribution;
//    private Button btn_weather;
    private TextView txt_result;

    private String result;

    //定义一个Handler用来更新页面：
    private Handler handler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case 0x001:
                    txt_result.setText("结果显示：\n" + result);
                    Toast.makeText(MainActivity.this, "获取信息成功", Toast.LENGTH_SHORT).show();
                    break;
                case 0x002:
                    txt_result.setText("结果显示：\n" + result);
                    Toast.makeText(MainActivity.this, "获取信息成功", Toast.LENGTH_SHORT).show();
                    break;
            }

        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        edit_param = (EditText) findViewById(R.id.edit_param);
        txt_result = (TextView) findViewById(R.id.txt_result);
        Button btn_query_xml_weather = (Button) findViewById(R.id.btn_query_xml_weather);
        Button btn_query_json_weather = (Button) findViewById(R.id.btn_query_json_weather);
        Button btn_query_soap_weather = (Button) findViewById(R.id.btn_query_soap_weather);
        Button btn_post_web_server = (Button) findViewById(R.id.btn_post_web_server);
        Button btn_protobuf = (Button) findViewById(R.id.btn_protobuf);
        btn_query_xml_weather.setOnClickListener(this);
        btn_query_json_weather.setOnClickListener(this);
        btn_query_soap_weather.setOnClickListener(this);
        btn_post_web_server.setOnClickListener(this);
        btn_protobuf.setOnClickListener(this);
    }


    @Override
    public void onClick(View v) {
        final String sss=edit_param.getText().toString();//北京
        switch (v.getId()) {
            case R.id.btn_query_xml_weather:
                new Thread() {
                    @Override
                    public void run() {
                        try {
                            result = getXmlWeather("北京");
                            handler.sendEmptyMessage(0x001);
                        }catch(Exception ex){
                            ex.printStackTrace();
                        }
                    }
                }.start();
                break;
            case R.id.btn_query_json_weather:
                new Thread() {
                    @Override
                    public void run() {
                        try {
                            result = getJsonWeather("北京");
                            System.out.print(result);
                            handler.sendEmptyMessage(0x001);
                        }catch(Exception ex){
                            ex.printStackTrace();
                        }
                    }
                }.start();
                break;
            case R.id.btn_query_soap_weather:
                new Thread() {
                    @Override
                    public void run() {
                        try {
                            result = getSoapWeather("北京");
                            System.out.print(result);
                            handler.sendEmptyMessage(0x001);
                        }catch(Exception ex){
                            ex.printStackTrace();
                        }
                    }
                }.start();
                break;

            case R.id.btn_post_web_server:
                new Thread(new Runnable() {
                    public void run() {
                        try {
                            result = postToWebServer();
                            System.out.print(result);
                            handler.sendEmptyMessage(0x001);
                        }catch(Exception ex){
                            ex.printStackTrace();
                        }
                    }
                }).start();
                break;
            case R.id.btn_protobuf:
                new Thread() {
                    @Override
                    public void run() {
                        try {
                            result=TestPb.getProtoBufString();
                            System.out.print(result);
                            handler.sendEmptyMessage(0x001);
                        }catch(Exception ex){
                            ex.printStackTrace();
                        }
                    }
                }.start();
                break;

        }
    }

    static String getInputStreamText(InputStream is) throws Exception {
        InputStreamReader isr = new InputStreamReader(is, "utf8");
        BufferedReader br = new BufferedReader(isr);
        StringBuilder sb=new StringBuilder();
        String line;
        while ((line = br.readLine()) != null) {
            sb.append(line);
        }
        return sb.toString();
    }
    public String postToWebServer() throws Exception {
                HttpURLConnection client = null;
           //     try {
                    byte[] data = new String("name="+java.net.URLEncoder.encode("测试", "UTF-8")+"&age=27").getBytes("UTF-8");
                    URL url = new URL("http://172.18.187.11:8080/jsp/getFromAndroid.jsp");
                    client = (HttpURLConnection) url.openConnection();
                    client.setRequestMethod("POST");
                    client.setConnectTimeout(1500);
                    client.setReadTimeout(1500);
                    client.setDoOutput(true);
                    client.setDoInput(true);
                    OutputStream out = client.getOutputStream();
                    out.write(data);
                    out.flush();
                    out.close();
                    //当调用getInputStream方法时才真正将请求体数据上传至服务器
                    InputStream is = client.getInputStream();
                    Log.d("TAG",client.getResponseCode()+"");  //打印响应状态码，200表明请求成功
                    return getInputStreamText(is);
    }
    public String getJsonWeather(String city) throws Exception{
        String apiUrl = String.format("http://172.18.187.9:8080/dict/");
        URL url= new URL(apiUrl);
        URLConnection open = url.openConnection();
        InputStream inputStream = open.getInputStream();
        return getInputStreamText(inputStream);
    }

    public String getXmlWeather(String city)  throws Exception{
        String city1 = java.net.URLEncoder.encode(city, "utf-8");
        String apiUrl = String.format("https://www.sojson.com/open/api/weather/xml.shtml?city=%s",city1);
        URL url= new URL(apiUrl);
        URLConnection open = url.openConnection();
        InputStream inputStream = open.getInputStream();
        return getInputStreamText(inputStream);
    }

    public String getSoapWeather(String city) throws Exception{
        //soap协议  基于http
        String service_url = "http://ws.webxml.com.cn/WebServices/WeatherWS.asmx";
        String name_space = "http://WebXml.com.cn/";
        String method_name = "getWeather";   //具体请求的服务

        HttpTransportSE httpTransportSE = new HttpTransportSE(service_url);         //创建信封
        SoapSerializationEnvelope envelope = new SoapSerializationEnvelope(SoapEnvelope.VER11);
        SoapObject soapObject = new SoapObject(name_space, method_name);
        soapObject.addProperty("theCityCode", city);
        soapObject.addProperty("theUserID", "905f90f0788f41498a29affacc38d27c");
        envelope.bodyOut = soapObject;
        envelope.dotNet = true;   //设置跨语言的兼容性
        httpTransportSE.call(name_space + method_name, envelope);   //连接服务器并发送请求
        if (envelope.getResponse() == null) {//判断响应消息不为空，如果为空就没有请求成功
            return "请求失败！";
        }
        // SoapObject result = (SoapObject) envelope.getResponse();
        SoapObject result1 = (SoapObject) envelope.bodyIn;
        //int count = result.getPropertyCount();   //得到属性集的数量
        SoapObject subSoapObj = (SoapObject) result1.getProperty("getWeatherResult");
        String ss = "属性个数: " + subSoapObj.getPropertyCount();
        for (int i = 0; i < subSoapObj.getPropertyCount(); i++) {
             SoapPrimitive childResult = (SoapPrimitive) subSoapObj.getProperty(i);
            ss=ss+"   " + childResult.getName()+":"+childResult.getValue();
        }
        return ss;
    }

}
