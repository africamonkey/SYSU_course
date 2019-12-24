package com.example.isszym.json2;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;
import com.google.gson.reflect.TypeToken;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;

class Phone {
    String type, number;
    void setType(String val) { type = val; }
    String getType() { return type;}
    void setNumber(String val) { number = val; }
    String getNumber() { return number;}
}

class Address {
    String streetAddress,city,state,postalCode;
    void setStreetAddress(String val) { streetAddress = val; }
    String getStreetAddress() { return streetAddress; }
    void setCity(String val) {city = val; }
    String getCity() {return city;}
    void setState(String val) { state = val; }
    String getState() { return state; }
    void setPostalCode(String val) {  postalCode = val; }
    String getPostalCode() { return  postalCode; }
}

class User {
    String firstName;
    String lastName;
    String sex;
    int age;
    Address address;
    List<Phone> phones;
    User(){
    }
    User(String firstName, String lastName, String sex, int age) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.sex = sex;
        this.age = age;
    }

    public void setFirstName(String val) { firstName = val; }
    public String getFirstName() { return firstName; }
    public void setLastName(String val) { lastName = val; }
    public String  getLastName() { return lastName; }
    public void setSex(String val) { sex = val; }
    public String getSex() { return sex; }
    public void setAge(int val) { age = val; }
    public int getAge(){ return age; }
    public void setAddress(Address val) { address = val;}
    public Address getAddress() { return address;}
    public void setPhoneNumber(List<Phone> phones) { this.phones = phones; }
    public List<Phone> getPhoneNumber() { return phones;}

    public String toString() {
        return "name: " + firstName + " " + lastName+", age: " + age;
    }
}

class GsonTools {

    /**TODO 转换为json字符串
     * @param src  要转换成json格式的 对象
     * @return
     */
    public static String createJsonString(Object src) {
        Gson gson = new Gson();
        String jsonString = gson.toJson(src);
        return jsonString;
    }


    /**TODO 转换为指定的 对象
     * @param jsonString
     * @param type 指定对象的类型 ，即 T.class
     * @return
     */
    public static <T> T getObject(String jsonString, Class<T> type) {
        T t = null;
        try {
            Gson gson = new Gson();
            t = gson.fromJson(jsonString, type);
        } catch (JsonSyntaxException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return t;
    }

    /**得到 一个List<T>集合
     * @param jsonString
     * @param type  T的类型
     * @return
     */
    public static <T> List<T> getList(String jsonString, Class<T> type) {
        List<T> list = new ArrayList<T>();
        Gson gson = new Gson();
        list = gson.fromJson(jsonString, new TypeToken<List<T>>() {
        }.getType());
        return list;

    }

    /**TODO 得到一个List<T> 的集合
     * @param jsonString json字符串
     * @param type  数组的类型 ，即T[].class
     * @return
     */
    public static <T> List<T> StringTolist(String jsonString, Class<T[]> type) {
        T[] list = null;
        try {
            Gson gson = new Gson();
            list = gson.fromJson(jsonString, type);
        } catch (JsonSyntaxException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        return Arrays.asList(list);

    }
    /**把json字符串转换为 String 集合
     * @param jsonString
     * @return
     */
    public static List<String> getStrings(String jsonString) {
        List<String> list = new ArrayList<String>();
        Gson gson = new Gson();
        new TypeToken<List<String>>(){}.getType();
        list = gson.fromJson(jsonString, new TypeToken<List<String>>() {
        }.getType());
        return list;

    }

    /**TODO 将json数据解析为Map<String,Object>集合
     * @param jsonString
     * @return
     */
    public static List<Map<String, Object>> getMaps(String jsonString) {

        List<Map<String, Object>> list = new ArrayList<Map<String, Object>>();
        Gson gson = new Gson();
        list = gson.fromJson(jsonString,
                new TypeToken<List<Map<String, Object>>>() {
                }.getType());

        return list;

    }
}

public class MainActivity extends AppCompatActivity {
    String user1 = "{\n" +
            "     \"firstName\": \"John\",\n" +
            "     \"lastName\": \"Smith\",\n" +
            "     \"sex\": \"male\",\n" +
            "     \"age\": 25,\n" +
            "     \"address\": \n" +
            "     {\n" +
            "         \"streetAddress\": \"21 2nd Street\",\n" +
            "         \"city\": \"New York\",\n" +
            "         \"state\": \"NY\",\n" +
            "         \"postalCode\": \"10021\"\n" +
            "     },\n" +
            "     \"phoneNumber\": \n" +
            "     [\n" +
            "         {\n" +
            "           \"type\": \"home\",\n" +
            "            \"number\": \"212 555-1234\"\n" +
            "         },\n" +
            "         {\n" +
            "           \"type\": \"fax\",\n" +
            "           \"number\": \"646 555-4567\"\n" +
            "         }\n" +
            "     ]\n" +
            " }";
    String phones =
            "     [\n" +
            "         {\n" +
            "           \"type\": \"home\",\n" +
            "            \"number\": \"212 555-1234\"\n" +
            "         },\n" +
            "         {\n" +
            "           \"type\": \"fax\",\n" +
            "           \"number\": \"646 555-4567\"\n" +
            "         }\n" +
            "     ]\n";
    User user;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView textView=(TextView)findViewById(R.id.textView);
        textView.setText(user1);
    }

    public static User parserJSON(String str) {
        JSONObject userObj=null;
        try {
            userObj = new JSONObject(str);
        } catch (Exception ex) {
            ex.printStackTrace();
        }
        User user = new User();
        user.setFirstName(userObj.optString("firstName"));
        user.setLastName(userObj.optString("lastName"));
        user.setSex(userObj.optString("sex"));
        user.setAge(userObj.optInt("age"));

        JSONObject addressObj = userObj.optJSONObject("address");

        Address address = new Address();
        address.setStreetAddress(addressObj.optString("streetAddress"));
        address.setCity(addressObj.optString("city"));
        address.setState(addressObj.optString("state"));
        address.setPostalCode(addressObj.optString("postalCode"));

        user.setAddress(address);

        JSONArray phoneNumber = userObj.optJSONArray("phoneNumber");

        List<Phone> phones = new ArrayList<>();
        for (int i = 0; i < phoneNumber.length(); i++) {
            Phone phone = new Phone();
            JSONObject phoneObj = phoneNumber.optJSONObject(i);
            phone.setType(phoneObj.optString("type"));
            phone.setNumber(phoneObj.optString("number"));
            phones.add(phone);
        }
        user.setPhoneNumber(phones);

        return user;
    }

    public void jsonSerialize1(View vw) {
        String user1=GsonTools.createJsonString(user);
        Toast.makeText(this, user1,
                Toast.LENGTH_LONG).show();
    }

    public void jsonParse1(View vw) {
        user = GsonTools.getObject(user1,User.class);
        List<Phone> ph= GsonTools.getList(phones,Phone.class);
        user.setPhoneNumber(ph);
        Toast.makeText(this, user.toString(),
                Toast.LENGTH_LONG).show();
    }
}
