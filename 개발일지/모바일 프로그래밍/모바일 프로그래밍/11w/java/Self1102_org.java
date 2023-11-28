package com.example.chapter11;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Context;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Gallery;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

@SuppressWarnings("deprecation")
public class Self1102_org extends AppCompatActivity {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.self1102_main_org);
        setTitle("갤러리 영화 포스터(개선)");

        Gallery gallery = (Gallery) findViewById(R.id.gallery1);

        MyGalleryAdapter galAdapter = new MyGalleryAdapter(this);
        gallery.setAdapter(galAdapter);
    }

    public class MyGalleryAdapter extends BaseAdapter {

        Context context;
        Integer[] posterID = { R.drawable.mov11, R.drawable.mov12,
                R.drawable.mov13, R.drawable.mov14, R.drawable.mov15,
                R.drawable.mov16, R.drawable.mov17, R.drawable.mov18,
                R.drawable.mov19, R.drawable.mov20 };

        String[] posterTitle = { "레옹", "주먹왕 랄프2", "타짜","걸캅스", "도굴", "어벤저스",
                "엑시트", "캡틴 마블", "봉오동 전투", "분노의 질주"};

        public MyGalleryAdapter(Context c) {
            context = c;
        }

        public int getCount() {
            // TODO Auto-generated method stub
            return posterID.length;
        }

        public Object getItem(int arg0) {
            // TODO Auto-generated method stub
            return null;
        }

        public long getItemId(int position) {
            // TODO Auto-generated method stub
            return 0;
        }

        public View getView(int position, View convertView, ViewGroup parent) {
            ImageView imageview = new ImageView(context);
            imageview.setLayoutParams(new Gallery.LayoutParams(200, 300));
            imageview.setScaleType(ImageView.ScaleType.FIT_CENTER);
            imageview.setPadding(5, 5, 5, 5);
            imageview.setImageResource(posterID[position]);

            final int pos = position;
            imageview.setOnTouchListener(new View.OnTouchListener() {
                public boolean onTouch(View v, MotionEvent event) {
                    ImageView ivPoster = (ImageView) findViewById(R.id.ivPoster);
                    ivPoster.setScaleType(ImageView.ScaleType.FIT_CENTER);
                    ivPoster.setImageResource(posterID[pos]);

                    Toast toast = new Toast(getApplicationContext());
                    View toastView = (View) View.inflate(
                            getApplicationContext(), R.layout.toast_org, null);
                    TextView toastText = (TextView) toastView
                            .findViewById(R.id.textView1);
                    toastText.setText(posterTitle[pos]);
                    toast.setView(toastView);
                    toast.show();

                    return false;
                }
            });

            return imageview;
        }
    }

}
