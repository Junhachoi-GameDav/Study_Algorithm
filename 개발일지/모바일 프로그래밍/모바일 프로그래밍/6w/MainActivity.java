package com.example.chapter06;

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
                Intent intent = new Intent(MainActivity.this, Self0601.class) ;

                startActivity(intent) ;
            }
        });

        Button button2 = (Button) findViewById(R.id.button2) ;
        button2.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0602.class) ;

                startActivity(intent) ;
            }
        });

        Button button3 = (Button) findViewById(R.id.button3) ;
        button3.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0603.class) ;

                startActivity(intent) ;
            }
        });


        Button button8 = (Button) findViewById(R.id.button8) ;
        button8.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0606.class) ;

                startActivity(intent) ;
            }
        });

        Button button9 = (Button) findViewById(R.id.button9) ;
        button9.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0607.class) ;

                startActivity(intent) ;
            }
        });


        Button button1_org = (Button) findViewById(R.id.button1_org) ;
        button1_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0601_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button2_org = (Button) findViewById(R.id.button2_org) ;
        button2_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0602_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button3_org = (Button) findViewById(R.id.button3_org) ;
        button3_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0603_org.class) ;

                startActivity(intent) ;
            }
        });


        Button button8_org = (Button) findViewById(R.id.button8_org) ;
        button8_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0606_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button9_org = (Button) findViewById(R.id.button9_org) ;
        button9_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0607_org.class) ;

                startActivity(intent) ;
            }
        });

    }
}