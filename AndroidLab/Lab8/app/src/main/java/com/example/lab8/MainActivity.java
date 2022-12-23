package com.example.lab8;

import androidx.appcompat.app.AppCompatActivity;
import android.gesture.Gesture;
import android.gesture.GestureLibraries;
import android.gesture.GestureLibrary;
import android.gesture.GestureOverlayView;
import android.gesture.GestureOverlayView.OnGesturePerformedListener;
import android.gesture.Prediction;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity implements OnGesturePerformedListener {

    private GestureLibrary lib;
    private TextView res;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //Связываемся с нашими объектами интерфейса:
        res = (TextView) findViewById(R.id.results);

        //Инициализируем библиотеку жестов, которые мы создали
        //в программе GestureBuilder и взяли оттуда файл с жестами:
        lib = GestureLibraries.fromRawResource(MainActivity.this, R.raw.gestures);
        if(!lib.load()){
            String t = "Библиотека не загружена";
            Toast.makeText(MainActivity.this, t, Toast.LENGTH_SHORT).show();
            finish();
        }

        //Инициализируем объект GestureOverlayView интерфейса приложения
        //и устанавливаем для него слушателя нарисованных жестов:
        GestureOverlayView gesture = (GestureOverlayView) findViewById(R.id.draw_gestures);
        gesture.addOnGesturePerformedListener(MainActivity.this);
    }

    //Обрабатываем рисование жестов в области GestureOverlayView:
    public void onGesturePerformed(GestureOverlayView overlay, Gesture gesture){

        //Здесь выполняется сравнение нарисованных пользователем
        //каракулей с заданными в библиотеке жестов (файле gestures), и после сравнения
        //выдается массив с цифрами, указывающими наибольшее сходство нарисованного с заданным в файле:
        ArrayList<Prediction> predictions = lib.recognize(gesture);
        String predict = "";
        NumberFormat format = new DecimalFormat("#0.00");
        for(int i = 0; i < predictions.size(); i++){
            Prediction prediction = predictions.get(i);

            //Отображается имя объектов с файла gestures и оценка их
            //сходства с нарисованным пользователем знаком в цифрах:
            predict = predict + prediction.name + " : " + format.format(prediction.score) + "\n";
        }

        //Результаты сравнений отображаем в элементе TextView:
        res.setText(predict);
    }

}