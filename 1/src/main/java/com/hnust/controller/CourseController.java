package com.hnust.controller;

import com.hnust.pojo.Course;
import com.hnust.service.CourseService;
import com.hnust.util.Constants;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import com.hnust.dto.paginationDTO;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletResponse;
import java.io.*;


@Controller
@ComponentScan("com.hnust.service")
@RequestMapping("/course")
public class CourseController {

    @Autowired
    private CourseService courseService;

    @RequestMapping("/allCourse")
    public String list(Model model,
                       @RequestParam(name="curPage",defaultValue = "1") Integer curPage,
                       @RequestParam(name = "pageSize",defaultValue = "3")Integer pageSize){
        paginationDTO paginationDTO = courseService.queryAllCourse(curPage,pageSize);
        model.addAttribute("list",paginationDTO);
        return "allCourse";

    }

    @RequestMapping("/toAddCourse")
    public String toAddPaper() {

        return "addCourse";
    }

    /**
     * 跳转到注册页面
     * @param model
     * @return
     */
    @RequestMapping(value="/addCourse", method = RequestMethod.GET)
    public String addPaper(Model model){
        Course course = new Course();
        model.addAttribute("course", course); // user 加入到 request 域
        return "addCourse"; // 跳转到 user/register.jsp 页面
    }

    /**
     * 处理用户注册的表单请求
     * @param course
     * @param file
     * @return
     */
    @RequestMapping(value = "/addCourse", method = RequestMethod.POST)
    public String addCourse(Course course,
                            @RequestParam("imgFile") MultipartFile file,
                            Model model){
        if (courseService.add(course, file)){
            model.addAttribute("course", course);
            return "redirect:/course/allCourse"; // 注册成功，跳转到显示页面
        }
        return "redirect:/course/addCourse"; // 注册失败，重定向到注册页面
    }

    /**
     * 处理图片显示请求
     * @param fileName
     */
    @RequestMapping("/showPic/{fileName}.{suffix}")
    public void showPicture(@PathVariable("fileName") String fileName,
                            @PathVariable("suffix") String suffix,
                            HttpServletResponse response){
        File imgFile = new File(Constants.IMG_PATH + fileName + "." + suffix);
        responseFile(response, imgFile);
    }


    /**
     * 响应输出图片文件
     * @param response
     * @param imgFile
     */
    private void responseFile(HttpServletResponse response, File imgFile) {
        try(InputStream is = new FileInputStream(imgFile);
            OutputStream os = response.getOutputStream();){
            byte [] buffer = new byte[1024]; // 图片文件流缓存池
            while(is.read(buffer) != -1){
                os.write(buffer);
            }
            os.flush();
        } catch (IOException ioe){
            ioe.printStackTrace();
        }
    }

    @RequestMapping("/toUpdateCourse")
    public String toUpdateCourse(Model model, int id) {
        Course course = courseService.queryCourseById(id);
        System.out.println(course);
        model.addAttribute("course",course );
        return "updateCourse";
    }


    /**
     * 跳转到注册页面
     * @param model
     * @return
     */
    @RequestMapping(value="/updateCourse", method = RequestMethod.GET)
    public String update(Model model){
        /*
         为什么这里要 new 一个 User 对象？
         因为我们在 JSP 页面中使用了 spring form 标签
         spring form 标签的 modelAttribute 默认需要一个对象用于接收数据
         这里我们是新增，所以用无参构造创建一个空对象（不是null）
          */
        Course course = new Course();
        model.addAttribute("course", course); // user 加入到 request 域
        return "updateCourse"; // 跳转到 user/register.jsp 页面
    }


    @RequestMapping(value = "/updateCourse", method = RequestMethod.POST)
    public String updateCourse(Course course,
                             @RequestParam("imgFile") MultipartFile file,
                             Model model){
        if (courseService.update(course, file)){
            model.addAttribute("course", course);
            return "redirect:/course/allCourse"; // 注册成功，跳转到显示页面
        }
        return "redirect:/course/updateCourse"; // 注册失败，重定向到注册页面
    }

    @RequestMapping("/updateCourse")
    public String updateCourse(Model model, Course course) {
        System.out.println(course);
        courseService.updateCourse(course);
        Course course1 = courseService.queryCourseById(course.getId());
        model.addAttribute("course", course);
        return "redirect:/course/allCourse";
    }

    @RequestMapping("/del/{id}")
    public String deleteCourse(@PathVariable("id") int id) {
        courseService.deleteCourseById(id);
        return "redirect:/course/allCourse";
    }

    @RequestMapping("/queryCourse")
    public String queryCourseByName(@RequestParam(name = "name",required = false)String name,
                                  @RequestParam(name="curPage",defaultValue = "1") Integer curPage,
                                  @RequestParam(name = "pageSize",defaultValue = "3")Integer pageSize,
                                  Model model){
        int count = courseService.queryCourseCountByName(name);
        if (count == 0){
            model.addAttribute("error","未查到相关书籍");
            model.addAttribute("list",null);
            return "allCourse";
        }
        paginationDTO paginationDTO = courseService.queryCourseByName(name, curPage, pageSize);
        model.addAttribute("name",name);
        model.addAttribute("list",paginationDTO);
        return "allCourse";
    }

}
