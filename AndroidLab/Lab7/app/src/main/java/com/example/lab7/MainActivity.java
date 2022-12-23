package com.example.lab7;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.os.Bundle;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.OvershootInterpolator;
import android.widget.FrameLayout;

public class MainActivity extends AppCompatActivity {
    private static final String DEBUG_TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        FrameLayout frame = (FrameLayout) findViewById(R.id.frame);
        PlayAreaView image = new PlayAreaView(MainActivity.this);
        frame.addView(image);

    }

    private class PlayAreaView extends View {

        private Matrix translate;
        private Bitmap droid;
        private GestureDetector gestures;
        private Matrix animateStart;
        private OvershootInterpolator animateInterpolator;
        private long startTime;
        private long endTime;
        private float totalAnimX;
        private float totalAnimY;

        public PlayAreaView(Context context) {
            super(context);
            translate = new Matrix();
            gestures = new GestureDetector(MainActivity.this, new GestureListener(this));
            droid = BitmapFactory.decodeResource(getResources(), R.drawable.apple);
        }

        @Override
        protected void onDraw(Canvas canvas) {
            canvas.drawBitmap(droid, translate, null);
            Matrix m = canvas.getMatrix();
            Log.d(DEBUG_TAG, "Matrix: "+ translate.toShortString());
            Log.d(DEBUG_TAG, "Canvas: "+ m.toShortString());
        }

        //метод который будет принимать данные о жестах и обрабатывать их
        @Override
        public boolean onTouchEvent(MotionEvent event) {
            return gestures.onTouchEvent(event);
        }

        // переводит изображение на расстояние в соответствии с движением пальца,
        // во вторых, аннулирует предыдущее положение изображения
        public void onMove(float dx, float dy) {
            translate.postTranslate(dx, dy);
            invalidate();
        }

        // метод будет просто сбрасывать все настройки на настройки по умолчанию
        public void onResetLocation() {
            translate.reset();
            invalidate();
        }

        // метод задания анимации
        public void onAnimateMove(float dx, float dy, long duration) {
            animateStart = new Matrix(translate);
            animateInterpolator = new OvershootInterpolator();
            startTime = System.currentTimeMillis();
            endTime = startTime + duration;
            totalAnimX = dx;
            totalAnimY = dy;
            post(new Runnable() {
                @Override
                public void run() {
                    onAnimateStep();
                }
            });
        }

        private void onAnimateStep() {
            long curTime = System.currentTimeMillis();
            float percentTime = (float) (curTime - startTime) / (float) (endTime - startTime);
            float percentDistance = animateInterpolator.getInterpolation(percentTime);
            float curDx = percentDistance * totalAnimX;
            float curDy = percentDistance * totalAnimY;
            translate.set(animateStart);
            onMove(curDx, curDy);
            if (percentTime < 1.0f) {
                post(new Runnable() {
                    @Override
                    public void run() {
                        onAnimateStep();
                    }
                });
            }
        }

    }

    // Класс, отвечающий за жесты
    // это двойное нажатие по экрану и направленные движения (влево, вправо и т.д.)
    private class GestureListener implements GestureDetector.OnGestureListener,
            GestureDetector.OnDoubleTapListener {

        PlayAreaView view;

        public GestureListener(PlayAreaView view){
            this.view = view;
        }

        @Override
        public boolean onSingleTapConfirmed(MotionEvent e) {
            Log.v(DEBUG_TAG, "onSingleTapConfirmed");
            return false;
        }

        // метод, который по двойному клику будет возвращать
        // на экран заблудшее за рамками экрана изображение
        @Override
        public boolean onDoubleTap(MotionEvent e) {
            Log.v(DEBUG_TAG, "onDoubleTap");
            view.onResetLocation(); // сбрасываем положение картинки на ее положение по умолчанию
            return true;
        }

        @Override
        public boolean onDoubleTapEvent(MotionEvent e) {
            Log.v(DEBUG_TAG, "onDoubleTapEvent");
            return false;
        }

        @Override
        public boolean onDown(MotionEvent e) {
            Log.v(DEBUG_TAG, "OnDown");
            return true;
        }

        @Override
        public void onShowPress(MotionEvent e) {
            Log.v(DEBUG_TAG, "onShowPress");
        }

        @Override
        public boolean onSingleTapUp(MotionEvent e) {
            Log.v(DEBUG_TAG, "onSingleTapUp");
            return false;
        }

        // Прокрутка. Оно происходит тогда, когда пользователь прикасается
        // к экрану и, не отрывая пальца, ведет им в какую либо сторону
        @Override
        public boolean onScroll(MotionEvent e, MotionEvent e1, float x, float y) {
            Log.v(DEBUG_TAG, "OnScroll");
            view.onMove(-x, -y);
            return true;
        }

        @Override
        public void onLongPress(MotionEvent e) {
            Log.v(DEBUG_TAG, "onLongPress");
        }

        // мы резким движением как бы толкаем картинку в определенную сторону,
        // убираем палец, а она летит по инерции в указанном направлении,
        // постепенно замедляя скорость до полной остановки
        @Override
        public boolean onFling(MotionEvent e, MotionEvent e1, float x, float y) {
            Log.v(DEBUG_TAG, "onFling");
            final float distanceTime = 0.3f; // 300мс
            final float totalX = (distanceTime * x/2);
            final float totalY = (distanceTime * y/2);
            view.onAnimateMove(totalX, totalY, (long)(1000 * distanceTime));
            return true;
        }
    }

}

