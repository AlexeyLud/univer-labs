package com.example.lab9;

import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.Manifest;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.hardware.Camera;
import android.os.Build;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import java.io.FileOutputStream;
import java.io.IOException;
import androidx.appcompat.app.AppCompatActivity;

public class CameraActivity extends AppCompatActivity {

    private Button click;
    private Context context;
    private Camera camera;
    private SurfaceHolder holder;
    private HolderCallback holderCallback;
    private SurfaceView preview;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_camera);

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (checkSelfPermission(Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
                requestPermissions(new String[] {Manifest.permission.CAMERA}, 1);
            }
        }

        context = this;
        click = (Button) findViewById(R.id.button_click);
        preview = (SurfaceView) findViewById(R.id.sv1);
        holder = preview.getHolder();
        holderCallback = new HolderCallback();
        holder.addCallback(holderCallback);

        this.click.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                camera.takePicture(null, null, null, new Camera.PictureCallback() {
                    @Override
                    public void onPictureTaken(byte[] bytes, Camera camera) {
                        try {
                            FileOutputStream os = new FileOutputStream(
                                    String.format("/storage/emulated/0/%d.jpg", System.currentTimeMillis())
                            );
                            os.write(bytes);
                            System.out.println("File write success!!!!!!!!!!!");
                            os.close();
                        }catch (IOException e) {
                            e.printStackTrace();
                        }
                        camera.startPreview();
                    }
                });
            }
        });
    }
    @Override
    protected void onResume() {
        super.onResume();
        camera = Camera.open();
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (camera != null) {
            camera.setPreviewCallback(null);
            camera.stopPreview();
            camera.release();
        }
        camera = null;
    }

    class HolderCallback implements SurfaceHolder.Callback {

        @Override
        public void surfaceCreated(SurfaceHolder holder) {
            try {
                camera.setPreviewDisplay(holder);
            } catch (IOException e) {
                e.printStackTrace();
            }

            Camera.Size previewSize = camera.getParameters().getPreviewSize();
            float aspect = (float) previewSize.width/previewSize.height;
            int psw = preview.getWidth();
            int psh = preview.getHeight();
            ViewGroup.LayoutParams lp = preview.getLayoutParams();

            if(context.getResources().getConfiguration().orientation != Configuration.ORIENTATION_LANDSCAPE){
                camera.setDisplayOrientation(90);
                lp.height = psh;
                lp.width = (int)(psw/aspect);
            }
            else{
                camera.setDisplayOrientation(0);
                lp.height = (int)(psh/aspect);
                lp.width = psw;
            }

            preview.setLayoutParams(lp);
            camera.startPreview();

        }

        @Override
        public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) { }

        @Override
        public void surfaceDestroyed(SurfaceHolder holder) { }

    }

}