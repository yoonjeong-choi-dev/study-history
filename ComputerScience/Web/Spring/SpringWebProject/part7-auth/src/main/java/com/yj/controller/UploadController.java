package com.yj.controller;

import com.yj.domain.DeleteFileDTO;
import com.yj.domain.UploadFileDTO;
import lombok.extern.log4j.Log4j;
import net.coobird.thumbnailator.Thumbnailator;
import org.springframework.core.io.FileSystemResource;
import org.springframework.core.io.Resource;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.util.FileCopyUtils;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.UUID;

@RestController
@Log4j
@RequestMapping("/upload/*")
public class UploadController {
    static final String uploadPath = "/home/yjchoi/local-tmp/spring/board/uploads";

    public static String getUploadPath() {
        return uploadPath;
    }

    @PreAuthorize("isAuthenticated()")
    @PostMapping(value = "/", produces = MediaType.APPLICATION_JSON_UTF8_VALUE)
    @ResponseBody
    public ResponseEntity<List<UploadFileDTO>> uploadAjaxPost(MultipartFile[] uploadFiles) {
        String uploadDirPath = getDirectoryPath();
        File uploadDirFile = new File(uploadPath, uploadDirPath);
        if(!uploadDirFile.exists()) {
            uploadDirFile.mkdirs();
            log.info(uploadDirFile.getAbsolutePath() + " created");
        }

        List<UploadFileDTO> res = new ArrayList<>();

        for(MultipartFile file : uploadFiles) {
            UploadFileDTO ret = new UploadFileDTO();
            ret.setUploadPath(uploadDirPath);

            // IE 브라우저 요청 처리 : IE 에서는 파일의 전체 경로를 함께 보냄
            String uploadFileName = file.getOriginalFilename();
            uploadFileName = uploadFileName.substring(uploadFileName.lastIndexOf("\\") + 1);
            ret.setFileName(uploadFileName);

            // 중복 파일 처리를 위한 UUID 추가
            String uuidStr = UUID.randomUUID().toString();
            uploadFileName = uuidStr + "_" +  uploadFileName;
            ret.setUuid(uuidStr);

            File saveFile = new File(uploadDirFile, uploadFileName);
            log.info("save file : " + saveFile.getAbsolutePath());
            try {
                file.transferTo(saveFile);

                // check whether the file is an image
                if(checkImageType(saveFile)) {
                    ret.setIsImage(1);

                    FileOutputStream thumbnail = new FileOutputStream(new File(uploadDirFile    , "s_" + uploadFileName));
                    Thumbnailator.createThumbnail(file.getInputStream(), thumbnail, 100, 100);
                    thumbnail.close();
                } else {
                    ret.setIsImage(0);
                }

                res.add(ret);
            } catch (IOException ex) {
                log.error(ex.getMessage());
                ex.printStackTrace();
            }
        }

        return new ResponseEntity<>(res, HttpStatus.OK);
    }

    @PreAuthorize("isAuthenticated()")
    @DeleteMapping("/")
    @ResponseBody
    public ResponseEntity<String> deleteFiles(@RequestBody DeleteFileDTO dto) {
        File file;
        try {
            file = new File(uploadPath, URLDecoder.decode(dto.getFileName(), "UTF-8"));
            file.delete();

            // 이미지의 경우 원본 이미지도 삭제
            if(dto.getType().equals("image")) {
                String largeFileName = file.getAbsolutePath().replace("s_", "");
                file = new File(largeFileName);
                file.delete();
            }
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        return new ResponseEntity<>("deleted", HttpStatus.OK);
    }


    @GetMapping("/display")
    @ResponseBody
    public ResponseEntity<byte[]> getFile(String fileName) {
        File file = new File(uploadPath, fileName);

        ResponseEntity<byte[]> response = null;
        try {
            HttpHeaders header = new HttpHeaders();
            header.add("Content-Type", Files.probeContentType(file.toPath()));
            response = new ResponseEntity<>(FileCopyUtils.copyToByteArray(file), header, HttpStatus.OK);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return response;
    }

    @GetMapping(value = "/download", produces = MediaType.APPLICATION_OCTET_STREAM_VALUE)
    @ResponseBody
    public ResponseEntity<Resource> downloadFile(@RequestHeader("User-Agent") String userAgent, String fileName) {
        Resource resource = new FileSystemResource(uploadPath + "/" + fileName);

        if(!resource.exists()) {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }

        String resourceName = resource.getFilename();

        // remove uuid from file name
        resourceName = resourceName.substring(resourceName.indexOf("_") + 1);

        HttpHeaders headers = new HttpHeaders();

        // 클라이언트 종류 확인
        log.info("Header - User Agent : " + userAgent);
        String downloadFileName = null;
        try {
            if(userAgent.contains("Trident")) {
                log.info("The client browser is type of IE");
                downloadFileName = URLEncoder.encode(resourceName, "UTF-8").replaceAll("\\+", " ");
            } else if (userAgent.contains("Edge")) {
                log.info("The client browser is type of Edge");
                downloadFileName = URLEncoder.encode(resourceName, "UTF-8");
            } else {
                log.info("The client browser is based on Chrome");
                downloadFileName = new String(resourceName.getBytes(StandardCharsets.UTF_8), StandardCharsets.ISO_8859_1);
            }
            log.info("Download File Name : " + downloadFileName);
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }

        headers.add("Content-Disposition",
                "attachment; filename=" + downloadFileName);

        return new ResponseEntity<>(resource, headers, HttpStatus.OK);
    }


    private String getDirectoryPath() {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        Date date = new Date();

        String curDate = sdf.format(date);
        return curDate.replace("-", File.separator);
    }

    private boolean checkImageType(File file) {
        try {
            String contentType = Files.probeContentType(file.toPath());
            log.info("Content Type (MIME) : " + contentType);
            return contentType.startsWith("image") && !contentType.equals("image/vnd.microsoft.icon");
        } catch (IOException e) {
            e.printStackTrace();
        }

        return false;
    }
}
