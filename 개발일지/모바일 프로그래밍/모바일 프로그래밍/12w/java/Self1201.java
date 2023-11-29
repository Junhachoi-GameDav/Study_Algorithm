package com.example.chapter12;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.graphics.Canvas;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class Self1201 extends AppCompatActivity {
    Button btn1;
    EditText editText;
    myDB myDbHelper;
    SQLiteDatabase sqlDB;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.self1201_main);
        setTitle("제품 테이블");

        btn1 = (Button)findViewById(R.id.btn1);
        editText = (EditText)findViewById(R.id.editResult);
        myDbHelper = new myDB(this);
        btn1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sqlDB = myDbHelper.getReadableDatabase();
                Cursor cursor = sqlDB.rawQuery("SELECT * FROM product;", null);

                String str = "\n";

                while(cursor.moveToNext()){
                    str += cursor.getString(0) + ", "
                            + cursor.getString(1) + ", "
                            + cursor.getString(2) + ", "
                            + cursor.getString(3) + ", "
                            + cursor.getString(4) + "\r\n";
                }

                editText.setText(str);
                cursor.close();
                sqlDB.close();
            }
        });

    }

    public class myDB extends SQLiteOpenHelper{

        myDB(Context context){
            super(context, "Self1201", null, 1);
        }

        @Override
        public void onCreate(SQLiteDatabase db) {
            db.execSQL("CREATE TABLE product ( name char(20) PRIMARY KEY, price INTEGER, date CHAR(20), company CHAR(20), remain INTEGER);");
            db.execSQL("INSERT INTO product(name, price, date, company, remain) VALUES ('TV', 100,'2017.7.22', 'Samsung', 55);");
            db.execSQL("INSERT INTO product(name, price, date, company, remain) VALUES ('Computer', 150, '2019.5.5', 'LG', 7);");
            db.execSQL("INSERT INTO product(name, price, date, company, remain) VALUES ('Monitor', 50, '2021.9.9', 'Daewoo', 33);");
        }

        @Override
        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            db.execSQL("DROP TABLE IF EXISTS product");
            onCreate(db);
        }
    }
}