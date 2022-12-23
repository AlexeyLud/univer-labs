package com.example.lab10;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Build;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private TextView width; // широта
    private TextView length; // долгота
    private TextView out;
    private LocationManager mlocManager;
    private LocationListener mlocListener;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
    }

    private void check(){

        if (mlocManager.isProviderEnabled(LocationManager.NETWORK_PROVIDER)) {
            out.setText("GPS включён");
        } else {
            out.setText("GPS не включён");
        }

        //Подписываемся на изменения в показаниях датчика
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M &&
                ActivityCompat.checkSelfPermission(
                        this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED &&
                ActivityCompat.checkSelfPermission(
                        this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED)
        {
            requestPermissions(new String[]{Manifest.permission.ACCESS_COARSE_LOCATION,
                    Manifest.permission.ACCESS_FINE_LOCATION}, 1);

        } else
        {
            mlocManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, 0, 0, mlocListener);
        }
    }


    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == 1 && grantResults[0] == RESULT_OK) {
            check();
        }
    }

    private void init(){
        width = (TextView) findViewById(R.id.textShirota);
        length = (TextView) findViewById(R.id.textDolgota);
        out = (TextView) findViewById(R.id.textOut);
        //Получаем сервис
        mlocManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
        mlocListener = new LocationListener() {
            @Override
            public void onLocationChanged(Location location) {
                String w = "Широта = " + location.getLatitude();
                width.setText(w);
                String l = "Долгота = " + location.getLongitude();
                length.setText(l);
            }

            @Override
            public void onProviderDisabled(String provider) { }

            @Override
            public void onProviderEnabled(String provider) { }

            @Override
            public void onStatusChanged(String provider, int status, Bundle extras) { }

        };
        check();
    }

}