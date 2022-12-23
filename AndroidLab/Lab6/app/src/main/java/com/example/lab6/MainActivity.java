package com.example.lab6;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;


public class MainActivity extends AppCompatActivity {

    private Button next_window_button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        next_window_button = (Button)findViewById(R.id.button_2);
        this.next_window_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String t = "Вы перешли на окно покупки";
                // Уведомление
                Toast.makeText(MainActivity.this, t, Toast.LENGTH_SHORT).show();
                Intent intent = new Intent(MainActivity.this, SecondActivity.class);
                startActivity(intent);
            }
        });
    }
}