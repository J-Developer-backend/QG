package com.Huangjian.util;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.net.URLDecoder;
import java.util.Enumeration;

public class ServletUtil {
    public static String[] getParams(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        String[] arr = new String[2];
        String method = req.getMethod();
        String params = "";
        if("GET".equals(method)){
            params = req.getQueryString();
            arr[0] = req.getParameter("username");
            arr[1] = req.getParameter("password");
        } else if ("POST".equals(method)) {
            BufferedReader reader = req.getReader();
            params = reader.readLine();
            String[] split = params.split("&");
            String[] name = split[0].split("=");
            String[] password = split[1].split("=");
            if(name.length == 1)
                arr[0] = null;
            else
                arr[0] = name[1];
            if(password.length == 1)
                arr[1] = null;
            else
                arr[1] = password[1];
        }
        String uri = req.getRequestURI();
        //请求行
        System.out.println("请求行:"+method + uri);
        Enumeration<String> headerNames = req.getHeaderNames();
        //请求头
        while(headerNames.hasMoreElements()){
            String s = headerNames.nextElement();
            String header = req.getHeader(s);
            System.out.println("请求头:"+s + ":" + header);
        }
        //请求体
        System.out.println("请求体:"+params);
        System.out.println("-------------------------------------------");
        if(arr[0]!=null)
            arr[0] = URLDecoder.decode(arr[0],"utf-8");
        if(arr[1]!=null)
            arr[1] = URLDecoder.decode(arr[1],"utf-8");
        return arr;
    }
}
