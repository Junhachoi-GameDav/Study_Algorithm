package com.example.chapter07;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button button1 = (Button) findViewById(R.id.button1) ;
        button1.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0701.class) ;

                startActivity(intent) ;
            }
        });

        Button button2 = (Button) findViewById(R.id.button2) ;
        button2.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0702.class) ;

                startActivity(intent) ;
            }
        });

        Button button3 = (Button) findViewById(R.id.button3) ;
        button3.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0703.class) ;

                startActivity(intent) ;
            }
        });


        Button button6 = (Button) findViewById(R.id.button6) ;
        button6.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0704.class) ;

                startActivity(intent) ;
            }
        });

        Button button7 = (Button) findViewById(R.id.button7) ;
        button7.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0705.class) ;

                startActivity(intent) ;
            }
        });

        Button button8 = (Button) findViewById(R.id.button8) ;
        button8.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0706.class) ;

                startActivity(intent) ;
            }
        });

        Button button1_org = (Button) findViewById(R.id.button1_org) ;
        button1_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0701_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button2_org = (Button) findViewById(R.id.button2_org) ;
        button2_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0702_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button3_org = (Button) findViewById(R.id.button3_org) ;
        button3_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0703_org.class) ;

                startActivity(intent) ;
            }
        });


        Button button6_org = (Button) findViewById(R.id.button6_org) ;
        button6_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0704_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button7_org = (Button) findViewById(R.id.button7_org) ;
        button7_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0705_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button8_org = (Button) findViewById(R.id.button8_org) ;
        button8_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0706_org.class) ;

                startActivity(intent) ;
            }
        });

    }
}