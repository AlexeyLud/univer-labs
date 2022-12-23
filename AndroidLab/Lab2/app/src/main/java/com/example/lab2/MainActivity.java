package com.example.lab2;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.*;

public class MainActivity extends AppCompatActivity {

    TextView text_view;
    EditText input_text;
    Button button;

    int rand_num;
    boolean end_or_not;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        text_view = (TextView)findViewById(R.id.textView); //возвращает объект класса TextView
        input_text = (EditText)findViewById(R.id.editText); //возвращает объект класса EditText
        button = (Button)findViewById(R.id.button); //возвращает объект класса Button

        rand_num = (int)(Math.random()*100);
        end_or_not = false;
    }

    public void Click(View view){
        input_text.setEnabled(true);
        if (!end_or_not){
            int in = Integer.parseInt(input_text.getText().toString()); // получ зн из поля ввода
            if (in > rand_num) // если оно больше нашего загаданного
                text_view.setText(getResources().getString(R.string.ahead)); // Многовато
            if (in < rand_num) // если оно меньше нашего загаданного
                text_view.setText(getResources().getString(R.string.behind)); // Маловато
            if (in == rand_num) // если оно равно нашему загаданному
            {
                text_view.setText(getResources().getString(R.string.hit)); // Мы победили
                button.setText(getResources().getString(R.string.play_more)); // кнопка предлогает сыграть ещё
                end_or_not = true;
                input_text.setEnabled(false);
            }
        }
        else
        {
            rand_num = (int)(Math.random()*100);
            button.setText(getResources().getString(R.string.start));
            text_view.setText(getResources().getString(R.string.try_to_guess));
            end_or_not = false;
        }
        input_text.setText("");
    }
}