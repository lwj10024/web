package com.hnust.interceptor;


import org.springframework.stereotype.Component;
import org.springframework.web.servlet.HandlerInterceptor;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@Component
public class UserInterceptor implements HandlerInterceptor {

    //编写拦截器，一般只需要重写preHandle方法即可
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        System.out.println("拦截前");

        if (request.getRequestURI().contains("login")){
            //登录请求不拦截
            return true;
        }

        if (request.getSession().getAttribute("u")!=null){
            //存在session，不拦截，不存在就拦截
            return true;
        }else if(request.getSession().getAttribute("u")==null) {
            request.setAttribute("msg","请登录后再试！");
            request.getRequestDispatcher("/WEB-INF/jsp/login.jsp").forward(request,response);
            return true;
        }

        //返回值为false，表示拦截请求，返回值为true表示不拦截，放行请求
        return false;
    }

    //下面两个方法一般用于做日志
    @Override
    public void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, ModelAndView modelAndView) throws Exception {

    }

    @Override
    public void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) throws Exception {
    }
}
