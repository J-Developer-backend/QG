package com.Huangjian.servlet;

import com.Huangjian.util.ServletUtil;
import org.apache.commons.io.IOUtils;

import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.PrintWriter;


@WebServlet("/CheckFile")
public class CheckFile extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        ServletUtil.getParams(req,resp);
        String id = req.getParameter("id");
        if(id == ""){
            resp.setStatus(404);
            return;
        }
        id = new String(id.getBytes("ISO-8859-1"),"UTF-8");
        System.out.println("文件路径:"+ id );
        FileInputStream fis = null;
        try {
            fis = new FileInputStream(id);
            ServletOutputStream sos = resp.getOutputStream();
            IOUtils.copy(fis,sos);
            sos.flush();
        } catch (IOException e) {
            PrintWriter writer = resp.getWriter();
            writer.write("cannot find the file");
            writer.flush();
        } finally {
            if(fis!=null)
                fis.close();
        }

    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doGet(req, resp);
    }
}
