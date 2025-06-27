package org.nazarik.dymMob;

import android.app.Activity;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Toast;

public class MainActivity extends Activity {
  private EditText urlInput;
  private ImageButton pasteButton;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);

    urlInput = findViewById(R.id.input_url);
    pasteButton = findViewById(R.id.paste_button);

    pasteButton.setOnClickListener(new View.OnClickListener() {
      @Override
      public void onClick(View v) {
        pasteFromClipboard();
      }
    });

    setActionButton(R.id.option1, 1);
    setActionButton(R.id.option2, 2);
    setActionButton(R.id.option3, 3);
    setActionButton(R.id.option4, 4);
    setActionButton(R.id.option5, 5);
  }

  private void setActionButton(int id, final int actionCode) {
    Button button = findViewById(id);
    button.setOnClickListener(new View.OnClickListener() {
      @Override
      public void onClick(View v) {
        String url = urlInput.getText().toString().trim();
        if (url.isEmpty()) {
          Toast.makeText(MainActivity.this, "Введите URL", Toast.LENGTH_SHORT).show();
          return;
        }

        Intent intent = new Intent(MainActivity.this, ConsoleActivity.class);
        intent.putExtra("url", url);
        intent.putExtra("action", actionCode);
        startActivity(intent);
      }
    });
  }

  private void pasteFromClipboard() {
    ClipboardManager clipboard = (ClipboardManager) getSystemService(CLIPBOARD_SERVICE);
    if (clipboard != null && clipboard.hasPrimaryClip()) {
      ClipData clip = clipboard.getPrimaryClip();
      if (clip != null && clip.getItemCount() > 0) {
        CharSequence text = clip.getItemAt(0).getText();
        if (text != null) {
          urlInput.setText(text.toString());
        }
      }
    }
  }
}

