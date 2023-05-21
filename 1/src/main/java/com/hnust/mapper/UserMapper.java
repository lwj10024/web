package com.hnust.mapper;

import com.hnust.pojo.User;
import org.apache.ibatis.annotations.*;
import org.springframework.stereotype.Repository;


@Repository
public interface UserMapper {

    //用户登录
    @Select("select * from user where email=#{email} AND password=#{password}")
    @Results(id = "userMap",value = {
            //id字段默认为false，表示不是主键
            //column表示数据库表字段，property表示实体类属性名。
            @Result(id = true,column = "id",property = "id"),
            @Result(column = "password",property = "password"),
            @Result(column = "email",property = "email")
    })
    //用户登录
    User login(User user);

}




