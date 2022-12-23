package com.example.lab3;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.*;

public class MainActivity extends AppCompatActivity {

    private static ImageView img_view;
    private static ImageButton lbtn;
    private static ImageButton dbtn;
    private int count1;
    private int count2;
    private int sumlike;
    private int sumdislike;
    int[] images = {R.drawable.dog, R.drawable.cat, R.drawable.laptop, R.drawable.tree, R.drawable.people};
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void LikeClick(View v){
        img_view = (ImageView)findViewById(R.id.imageView);
        lbtn = (ImageButton)findViewById(R.id.buttonLike);
        count1++;
        sumlike += count1;
        System.out.println("Количество лайков = " + sumlike);
        count1 = count1 % images.length;
        System.out.println("count1 = " + count1);
        img_view.setImageResource(images[count1]);
    }

    public void DislikeClick(View v){
        img_view = (ImageView)findViewById(R.id.imageView);
        dbtn = (ImageButton)findViewById(R.id.buttonDislike);
        count2++;
        sumdislike += count2;
        System.out.println("Количество дизлайков = " + sumdislike);
        count2 = count2 % images.length;
        System.out.println("count2 = " + count2);
        img_view.setImageResource(images[count2]);
    }
}