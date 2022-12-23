package com.example.lab9;

import androidx.appcompat.app.AppCompatActivity;

import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.MediaController;
import android.widget.VideoView;

public class AudioVideoActivity extends AppCompatActivity {

    private Button start;
    private Button pause;
    private Button reset;
    private MediaPlayer mp;
    private VideoView vv;
    private Button play;
    private Button stop;
    private Button resume;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audio_video);

        start = (Button) findViewById(R.id.start);
        pause = (Button) findViewById(R.id.pause);
        reset = (Button) findViewById(R.id.reset);

        mp = MediaPlayer.create(AudioVideoActivity.this, R.raw.sound);

        this.start.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mp.start();
            }
        });

        this.pause.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mp.pause();
            }
        });

        this.reset.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mp.stop();
                mp = MediaPlayer.create(AudioVideoActivity.this, R.raw.sound);
                mp.start();
            }
        });

        play = (Button) findViewById(R.id.play);
        stop = (Button) findViewById(R.id.stop);
        resume = (Button) findViewById(R.id.resume);
        vv = (VideoView) findViewById(R.id.videoView);

        Uri myVideoUri= Uri.parse( "android.resource://" + getPackageName() + "/" + R.raw.hedgehog);
        vv.setVideoURI(myVideoUri);
        vv.setMediaController(new MediaController(AudioVideoActivity.this));
        vv.requestFocus(0);

        this.play.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                vv.start();
            }
        });

        this.stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                vv.pause();
            }
        });

        this.resume.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                vv.stopPlayback();
                vv.resume();
                vv.start();
            }
        });

    }
}