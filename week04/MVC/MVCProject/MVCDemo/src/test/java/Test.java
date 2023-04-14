import com.Huangjian.po.User;
import com.Huangjian.util.QueryUtil;
import com.Huangjian.util.ResultUtil;
import com.alibaba.fastjson.JSON;

import java.util.HashMap;


public class Test {

    @org.junit.Test
    public void test(){
        User user = new User("zhansan","12456",1);
        HashMap<String,String> map = new HashMap<>();
        map.put("username", user.getUsername());
        map.put("password", user.getPassword());
        User query = QueryUtil.query(User.class, map);
        System.out.println(query);
        System.out.println(JSON.toJSONString(query));
        System.out.println(ResultUtil.result(query,200,"ok"));
    }
}
