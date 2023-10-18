package com.example.chapter05;

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
                Intent intent = new Intent(MainActivity.this, Self0501.class) ;

                startActivity(intent) ;
            }
        });

        Button button2 = (Button) findViewById(R.id.button2) ;
        button2.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0502.class) ;

                startActivity(intent) ;
            }
        });

        Button button3 = (Button) findViewById(R.id.button3) ;
        button3.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0503.class) ;

                startActivity(intent) ;
            }
        });

        Button button4 = (Button) findViewById(R.id.button4) ;
        button4.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0504.class) ;

                startActivity(intent) ;
            }
        });

        Button button5 = (Button) findViewById(R.id.button5) ;
        button5.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0505.class) ;

                startActivity(intent) ;
            }
        });

        Button button6 = (Button) findViewById(R.id.button6) ;
        button6.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0504.class) ;

                startActivity(intent) ;
            }
        });

        Button button7 = (Button) findViewById(R.id.button7) ;
        button7.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0505.class) ;

                startActivity(intent) ;
            }
        });

        Button button8 = (Button) findViewById(R.id.button8) ;
        button8.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0506.class) ;

                startActivity(intent) ;
            }
        });

        Button button9 = (Button) findViewById(R.id.button9) ;
        button9.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0507.class) ;

                startActivity(intent) ;
            }
        });


        Button button1_org = (Button) findViewById(R.id.button1_org) ;
        button1_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0501_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button2_org = (Button) findViewById(R.id.button2_org) ;
        button2_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0502_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button3_org = (Button) findViewById(R.id.button3_org) ;
        button3_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0503_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button4_org = (Button) findViewById(R.id.button4_org) ;
        button4_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0504_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button5_org = (Button) findViewById(R.id.button5_org) ;
        button5_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Self0505_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button6_org = (Button) findViewById(R.id.button6_org) ;
        button6_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0504_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button7_org = (Button) findViewById(R.id.button7_org) ;
        button7_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0505_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button8_org = (Button) findViewById(R.id.button8_org) ;
        button8_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0506_org.class) ;

                startActivity(intent) ;
            }
        });

        Button button9_org = (Button) findViewById(R.id.button9_org) ;
        button9_org.setOnClickListener(new Button.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, Exer0507_org.class) ;

                startActivity(intent) ;
            }
        });

    }
}