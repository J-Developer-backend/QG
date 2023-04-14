package com.Huangjian.util;


import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import com.alibaba.fastjson.serializer.SerializerFeature;

import java.util.HashMap;

public class ResultUtil {


    public static<T> String result(T t , Integer code , String msg){
        HashMap<String,Object> map = new HashMap<>();
        String s = JSON.toJSONString(t, SerializerFeature.WriteMapNullValue);
        JSONObject jsonObject = JSON.parseObject(s);
        map.put("data" , jsonObject);
        map.put("code",code.toString());
        map.put("msg",msg);
        return JSON.toJSONString(map, SerializerFeature.WriteMapNullValue);
    }


}
