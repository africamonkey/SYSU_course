package com.example.isszym.webservicedemo;

import java.util.List;

import com.google.protobuf.InvalidProtocolBufferException;
import com.example.isszym.webservicedemo.PersonProbuf;
import com.example.isszym.webservicedemo.PersonProbuf.Person;
import com.example.isszym.webservicedemo.PersonProbuf.Person.PhoneNumber;

public class TestPb {
	public static String getProtoBufString() {
		// TODO Auto-generated method stub
		PersonProbuf.Person.Builder builder = PersonProbuf.Person.newBuilder();
		builder.setEmail("kkk@email.com");
		builder.setId(1);
		builder.setName("TestName");
		builder.addPhone(PersonProbuf.Person.PhoneNumber.newBuilder().setNumber("131111111").setType(PersonProbuf.Person.PhoneType.MOBILE));
		builder.addPhone(PersonProbuf.Person.PhoneNumber.newBuilder().setNumber("011111").setType(PersonProbuf.Person.PhoneType.HOME));

		Person person = builder.build();
		byte[] buf = person.toByteArray();
        String res="";
		try {
			Person person2 = PersonProbuf.Person.parseFrom(buf);
			//System.out.println(person2.getName() + ", " + person2.getEmail());
			res=res+" name:"+person2.getName() + ", email:" + person2.getEmail();
			List<PhoneNumber> lstPhones = person2.getPhoneList();
			for (PhoneNumber phoneNumber : lstPhones) {
			//	System.out.println(phoneNumber.getNumber());
				res=res+" phone#:"+phoneNumber.getNumber();
			}
		} catch (InvalidProtocolBufferException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        return res;
		//System.out.println(buf);

	}

}
