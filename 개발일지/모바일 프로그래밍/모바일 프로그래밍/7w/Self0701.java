package com.example.chapter07;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.EditText;
import android.widget.ImageView;

public class Self0701 extends AppCompatActivity {

    EditText edtAngle;
    ImageView imageView1;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.self0701_main);
        getSupportActionBar().setDisplayShowHomeEnabled(true);
        getSupportActionBar().setIcon(R.drawable.ic_launcher);
        setTitle("제주도 풍경");

        edtAngle = (EditText) findViewById(R.id.edtAngle);
        imageView1 = (ImageView) findViewById(R.id.imageView1);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // TODO Auto-generated method stub
        super.onCreateOptionsMenu(menu);
        MenuInflater mInflater = getMenuInflater();
        mInflater.inflate(R.menu.menu0701, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.itemRotate:
                imageView1.setRotation(Float.parseFloat(edtAngle.getText()
                        .toString()));
                return true;
            case R.id.item1:
                imageView1.setImageResource(R.drawable.jeju2);
                return true;
            case R.id.item2:
                imageView1.setImageResource(R.drawable.jeju14);
                return true;
            case R.id.item3:
                imageView1.setImageResource(R.drawable.jeju6);
                return true;
            case R.id.itemRotate1:      // 추가
                imageView1.setScaleX(2);
                imageView1.setScaleY(2);
                return true;
            case R.id.itemRotate2:
                imageView1.setScaleX((float)0.5);
                imageView1.setScaleY((float)0.5);
                return true;
            case R.id.itemRotate3:
                imageView1.setScaleX((float)1.0);
                imageView1.setScaleY((float)1.0);
                return true;
        }
        return false;
    }
}