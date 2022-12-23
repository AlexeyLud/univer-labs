package com.example.jsonlist;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class MainActivity extends AppCompatActivity {

    private EditText input_text;
    private Button search_button;
    private TextView result;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        input_text = (EditText)findViewById(R.id.editText);
        search_button = (Button)findViewById(R.id.button);
        result = (TextView)findViewById(R.id.textView);

        this.search_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                result.clearComposingText();
                String t = input_text.getText().toString();
                int tt = Integer.parseInt(t);
                int id = tt - 1;
                if(id > 3){
                    result.setText(getResources().getString(R.string.not_found));
                }
                else{
                    runExample(view);
                }
            }
        });
    }

    public void runExample(View view)  {
        result.setEnabled(false);
        try {
            Search(this);
        } catch(Exception e){
            result.setText(e.getMessage());
            e.printStackTrace();
        }
    }

    public void Search(Context context) throws IOException,JSONException{
        String t = input_text.getText().toString();
        int tt = Integer.parseInt(t);
        int id = tt - 1;
        String jsonText = readText(context, R.raw.users);
        JSONObject root = new JSONObject(jsonText); // весь объект в { }
        JSONArray jsonArray = root.getJSONArray("response"); // массив response [ ]
        JSONObject userInfo = jsonArray.getJSONObject(id); // получаем объект по id
        String fname = userInfo.getString("fname");
        String lname = userInfo.getString("lname");
        String country = userInfo.getString("country");
        String city = userInfo.getString("city");
        String resulting = "Имя:  " + fname + "\n" + "Фамилия:  " + lname + "\n" +
                "Страна:  " + country + "\n" + "Город:  " + city;
        result.setText(resulting);
    }

    private static String readText(Context context, int resId) throws IOException {
        InputStream is = context.getResources().openRawResource(resId);
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        StringBuilder sb = new StringBuilder();
        String s = null;
        while( (s = br.readLine()) != null) {
            sb.append(s);
            sb.append("\n");
        }
        return sb.toString();
    }
}