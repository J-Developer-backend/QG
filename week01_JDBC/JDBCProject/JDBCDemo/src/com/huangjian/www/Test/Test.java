package com.huangjian.www.Test;

import com.huangjian.www.Util.JDBCUtil;

import javax.rmi.CORBA.Util;

public class Test {
    public static void main(String[] args) {
        Class<JDBCUtil> jdbcUtilClass = JDBCUtil.class;
        JDBCUtil.getConnection();
    }
}
