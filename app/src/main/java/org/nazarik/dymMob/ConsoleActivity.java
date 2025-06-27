package org.nazarik.dymMob;

import android.app.Activity;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;

public class ConsoleActivity extends Activity {
  private TextView consoleOutput;
  private Button retryButton;

  private String url;
  private int actionCode;

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_console);

    consoleOutput = findViewById(R.id.console_output);
    retryButton = findViewById(R.id.btn_download_another);
    retryButton.setEnabled(false);

    Intent intent = getIntent();
    url = intent.getStringExtra("url");
    actionCode = intent.getIntExtra("action", 0);

    prepareExecutable("dym");
    prepareConfig("config.ini");

    runShellCommand(url, actionCode);

    retryButton.setOnClickListener(v -> finish());
  }

  // Копирование бинарника dym в внутреннюю директорию
  private void prepareExecutable(String assetName) {
    File outFile = new File(getFilesDir(), assetName);
    if (!outFile.exists()) {
      copyAssetToFile(assetName, outFile);
      outFile.setExecutable(true);
    }
  }

  // Копирование конфигурационного файла
  private void prepareConfig(String assetName) {
    File outFile = new File(getFilesDir(), assetName);
    if (!outFile.exists()) {
      copyAssetToFile(assetName, outFile);
    }
  }

  private void copyAssetToFile(String assetName, File outFile) {
    try (InputStream in = getAssets().open(assetName);
         FileOutputStream out = new FileOutputStream(outFile)) {
      byte[] buffer = new byte[4096];
      int read;
      while ((read = in.read(buffer)) != -1) {
        out.write(buffer, 0, read);
      }
    } catch (Exception e) {
      consoleOutput.append("[ОШИБКА] Копирование " + assetName + ": " + e.getMessage() + "\n");
    }
  }

  private void runShellCommand(String url, int option) {
    new AsyncTask<Void, String, Integer>() {
      @Override
      protected Integer doInBackground(Void... voids) {
        try {
          String modeArg = "-" + option;
          String binaryPath = new File(getFilesDir(), "dym").getAbsolutePath();
          String configPath = new File(getFilesDir(), "config.ini").getAbsolutePath();

          String[] command = new String[] {
            binaryPath,
            "--config", configPath,
            modeArg,
            url
          };

          ProcessBuilder pb = new ProcessBuilder(command);
          pb.redirectErrorStream(true);
          pb.directory(getFilesDir()); // set working directory

          Process process = pb.start();

          BufferedReader reader = new BufferedReader(
            new InputStreamReader(process.getInputStream()));

          String line;
          while ((line = reader.readLine()) != null) {
            publishProgress(line);
          }

          int exitCode = process.waitFor();
          return exitCode;

        } catch (Exception e) {
          publishProgress("[ОШИБКА] " + e.getMessage());
          return -1;
        }
      }

      @Override
      protected void onProgressUpdate(String... values) {
        for (String line : values) {
          consoleOutput.append(line + "\n");
        }
      }

      @Override
      protected void onPostExecute(Integer result) {
        consoleOutput.append("\n[Завершено] Код выхода: " + result + "\n");
        retryButton.setEnabled(true);
      }
    }.execute();
  }
}

