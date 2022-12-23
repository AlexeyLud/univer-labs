package com.example.lab9;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import java.io.FileNotFoundException;
import java.io.InputStream;

public class ShowImageActivity extends AppCompatActivity {

    private final int Pick_image = 1;
    private Button photos;
    private ImageView im_vid;
    private Context context;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_show_image);

        context = this;
        im_vid = (ImageView) findViewById(R.id.imageView2);
        photos = (Button) findViewById(R.id.photos);

        this.photos.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                //Вызываем стандартную галерею для выбора изображения с помощью Intent.ACTION_PICK:
                Intent photoPickerIntent = new Intent(Intent.ACTION_PICK); // APP_PATH

                //Тип получаемых объектов - image:
                photoPickerIntent.setType("image/*");

                //Запускаем переход с ожиданием обратного результата в виде информации об изображении:
                startActivityForResult(photoPickerIntent, Pick_image);
            }
        });
    }

    //Обрабатываем результат выбора в галерее:
    @Override
    protected void onActivityResult(int req, int res, Intent intent) {
        super.onActivityResult(req, res, intent);
        switch (req) {
            case Pick_image:
                if (res == RESULT_OK) {
                    try {
                        //Получаем URI изображения, преобразуем его в Bitmap
                        //объект и отображаем в элементе ImageView нашего интерфейса:
                        final Uri imageUri = intent.getData();
                        System.out.println("image uri = " + imageUri.getPath());
                        final InputStream imageStream = getContentResolver().openInputStream(imageUri);
                        final Bitmap selectedImage = BitmapFactory.decodeStream(imageStream);
                        im_vid.setImageBitmap(selectedImage);
                    } catch (FileNotFoundException e) {
                        e.printStackTrace();
                    }
                }
        }
    }

}