package com.Huangjian.Util;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;

public class MybatisUtil {

    private static final String resource = "mybatis-config.xml";
    private static InputStream inputStream;
    static {
        try {
            inputStream = Resources.getResourceAsStream(resource);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    private static final SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);


    public static SqlSession getSession() {
        return sqlSessionFactory.openSession();
    }

}
