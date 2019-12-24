package com.example.isszym.json1;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

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
    User user;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView textView=(TextView)findViewById(R.id.textView);
        textView.setText(user1);
        System.out.print(user1);
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
    public static String toJSON(User user){
        JSONObject userObj = new JSONObject();
        try {
            userObj.put("firstName", user.getFirstName());
            userObj.put("lastName", user.getLastName());
            userObj.put("sex", user.getSex());
            userObj.put("age", user.getAge());

            JSONObject addressObj = new JSONObject();
            Address address = user.getAddress();
            addressObj.put("streetAddress", address.getStreetAddress());
            addressObj.put("city", address.getCity());
            addressObj.put("state", address.getState());
            addressObj.put("postalCode", address.getPostalCode());

            userObj.put("address", addressObj);

            List<Phone> phoneNumber = user.getPhoneNumber();
            JSONArray phoneArrayObj = new JSONArray();
            for (int i = 0; i < phoneNumber.size(); i++) {
                JSONObject phoneObj = new JSONObject();
                phoneObj.put("type", phoneNumber.get(i).getType());
                phoneObj.put("number", phoneNumber.get(i).getNumber());
                phoneArrayObj.put(phoneObj);
            }
            userObj.put("phoneNumber", phoneArrayObj);
        }
        catch(Exception ex){
            ex.printStackTrace();
        }
        return userObj.toString();
    }


    public void jsonSerialize1(View vw) {
        String user1=toJSON(user);
        Toast.makeText(this, user1,
                Toast.LENGTH_LONG).show();
    }

    public void jsonParse1(View vw) {
        user = parserJSON(user1);
        Toast.makeText(this, user.toString(),
                Toast.LENGTH_LONG).show();
    }
}
