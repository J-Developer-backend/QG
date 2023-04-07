package com.Huangjian.Util;

import com.alibaba.fastjson.JSON;

public class JsonStr {

    private Object data;
    private Integer status;
    private String msg;

    public JsonStr() {
    }

    public JsonStr(Object data, Integer status, String msg) {
        if(data==null)
            this.data ="{\"password\":\"error\",\"username\":\"error\"}";
        else
            this.data = JSON.toJSONString(data);
        this.status = status;
        this.msg = msg;
    }

    public Object getData() {
        return data;
    }

    public void setData(Object data) {
        this.data =JSON.toJSONString(data);
    }

    public Integer getStatus() {
        return status;
    }

    public void setStatus(Integer status) {
        this.status = status;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    @Override
    public String toString() {
        return "JsonStr{" +
                "data=" + data +
                ", status=" + status +
                ", msg='" + msg + '\'' +
                '}';
    }
}
