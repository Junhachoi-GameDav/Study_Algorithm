package com.example.chapter11;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle("리스트뷰 테스트");

        final String[] mid = {"직접 풀어보기 1 원본", "직접 풀어보기 1", "직접 풀어보기 2 원본", "직접 풀어보기 2", "직접 풀어보기 3 원본", "직접 풀어보기 3",
                "연습문제 5 원본", "연습문제 5","연습문제 6 원본", "연습문제 6"};

        ListView list = (ListView) findViewById(R.id.listView1);

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_list_item_1, mid);
        list.setAdapter(adapter);

        list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
                                    long arg3) {
                Intent intent = new Intent();
                if (arg2 == 0)
                    intent = new Intent(MainActivity.this, Self1101_org.class) ;
                else if (arg2 == 1)
                    intent = new Intent(MainActivity.this, Self1101.class) ;
                else if (arg2 == 2)
                    intent = new Intent(MainActivity.this, Self1102_org.class) ;
                else if (arg2 == 3)
                    intent = new Intent(MainActivity.this, Self1102.class) ;
                else if (arg2 == 4)
                    intent = new Intent(MainActivity.this, Self1103_org.class) ;
                else if (arg2 == 5)
                    intent = new Intent(MainActivity.this, Self1103.class) ;
                else if (arg2 == 6)
                    intent = new Intent(MainActivity.this, Exer1105_org.class) ;
                else if (arg2 == 7)
                    intent = new Intent(MainActivity.this, Exer1105.class) ;
                else if (arg2 == 8)
                    intent = new Intent(MainActivity.this, Exer1106_org.class) ;
                else
                    intent = new Intent(MainActivity.this, Exer1106.class) ;

                startActivity(intent) ;
                Toast.makeText(getApplicationContext(), mid[arg2],
                        Toast.LENGTH_SHORT).show();
            }
        });

    }
}