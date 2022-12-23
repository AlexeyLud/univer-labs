package com.example.lab6;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import androidx.core.app.NotificationCompat;

public class SecondActivity extends Activity {

    private Button buy_button;
    private Button back_to_main;
    private NotificationManager manager;
    private static final int mnID = 1001;
    private static String CHANNEL_ID = "My channel";
    private int count = 1;

    protected void onCreate(Bundle saveInstanceState){
        super.onCreate(saveInstanceState);
        setContentView(R.layout.second); // 2 окно

        manager = (NotificationManager)getApplicationContext().getSystemService(Context.NOTIFICATION_SERVICE);

        buy_button = (Button)findViewById(R.id.button);
        this.buy_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                AlertDialog dialog = getDialog();
                dialog.show();
            }
        });

        back_to_main = (Button) findViewById(R.id.back);
        this.back_to_main.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(SecondActivity.this, MainActivity.class);
                startActivity(intent);
            }
        });
    }

    public void createChannel(NotificationManager manager){
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
            NotificationChannel channel = new NotificationChannel(CHANNEL_ID, CHANNEL_ID,
                    NotificationManager.IMPORTANCE_DEFAULT);
            manager.createNotificationChannel(channel);
        }
        else{
            // Уведомление
            Toast.makeText(SecondActivity.this, "Ошибка!", Toast.LENGTH_SHORT).show();
        }
    }

    public AlertDialog getDialog(){
        // Диалоговое окно
        AlertDialog.Builder b = new AlertDialog.Builder(this);
        b.setTitle(R.string.title);
        b.setMessage(R.string.message);
        b.setCancelable(false);
        b.setIcon(R.drawable.apple2);
        b.setNegativeButton(R.string.no, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int i) {
                dialog.dismiss();
            }
        });
        b.setPositiveButton(R.string.ok, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int i) {
                // Уведомление
                Intent intent = new Intent(SecondActivity.this, MainActivity.class);
                PendingIntent pendingIntent = PendingIntent.getActivity(SecondActivity.this, 0,
                        intent, PendingIntent.FLAG_UPDATE_CURRENT);
                NotificationCompat.Builder builder =
                        new NotificationCompat.Builder(SecondActivity.this, CHANNEL_ID);
                String title = "Срочное сообщение";
                String text = "Вы купили " + count + " яблок(о)/(a)";
                builder.setSmallIcon(R.drawable.apple);
                builder.setTicker("У вас новое уведомление");
                builder.setWhen(System.currentTimeMillis());
                builder.setContentTitle(title);
                builder.setContentText(text);
                builder.setContentIntent(pendingIntent);
                builder.setAutoCancel(true);
                createChannel(manager);
                manager.notify(mnID, builder.build());
                count++;
                String t = "Вы совершили покупку";
                Toast.makeText(SecondActivity.this, t, Toast.LENGTH_SHORT).show();
                dialog.dismiss();
            }
        });
        return b.create();
    }
}
