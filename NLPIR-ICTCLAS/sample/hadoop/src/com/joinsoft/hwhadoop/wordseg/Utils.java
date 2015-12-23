package com.joinsoft.hwhadoop.wordseg;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.filecache.DistributedCache;
import org.apache.hadoop.fs.Path;

import java.io.*;
import java.net.URI;
import java.net.URL;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

/**
 * User: xingsen
 * Date: 13-11-3
 * Time: 上午11:32
 */
public class Utils {
    public static Path getPath(String fileName, Configuration configuration) throws IOException {
        Path[] localFiles = DistributedCache.getLocalCacheFiles(configuration);
        for (Path path : localFiles) {
            if (path.getName().indexOf(fileName) != -1) {
                return path;
            }
        }
        return null;
    }

    public static void putClassFile(String path, Configuration conf) throws IOException {
        Path file = new Path(path);
        DistributedCache.addFileToClassPath(file, conf, file.getFileSystem(conf));
    }

    public static void putFile(URI uri, Configuration configuration) {
        DistributedCache.addCacheFile(uri, configuration);
    }


    public static void unzipArchive(File archive)
            throws IOException {
        ZipFile zipfile = new ZipFile(archive);
        for (Enumeration<? extends ZipEntry> e = zipfile.entries(); e.hasMoreElements(); ) {
            ZipEntry entry = e.nextElement();
            unzipEntry(zipfile, entry, Utils.getRootPath());
        }
    }

    private static void unzipEntry(ZipFile zipfile, ZipEntry entry, File outputDir)
            throws IOException {

        if (entry.isDirectory()) {
            new File(outputDir, entry.getName()).mkdir();
            return;
        }

        File outputFile = new File(outputDir, entry.getName());
        if (!outputFile.getParentFile().exists())
            outputFile.getParentFile().mkdir();
        outputFile.createNewFile();
        BufferedInputStream inputStream = new BufferedInputStream(zipfile.getInputStream(entry));
        BufferedOutputStream outputStream = new BufferedOutputStream(new FileOutputStream(outputFile));

        try {
            byte buffer[] = new byte[1024 * 1024]; //1M
            int realLength;
            while ((realLength = inputStream.read(buffer)) > 0) {
                outputStream.write(buffer, 0, realLength);
            }
        } finally {
            outputStream.close();
            inputStream.close();
        }
    }

    public static File getRootPath() {
        URL url = Utils.class.getProtectionDomain().getCodeSource().getLocation();
        File file = new File(new File(url.getPath()).getParent() + "/");
        file.mkdirs();
        return file;
    }

    public static void cleanFile() {
        File data = new File(getRootPath() + "/Data");
        if (data.exists()) {
            data.delete();
        }
        File so = new File(getRootPath() + "/libNLPIR.so");
        if (so.exists()) {
            so.delete();
        }
    }
}
