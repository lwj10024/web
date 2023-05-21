package com.hnust.service;
import com.hnust.dto.paginationDTO;
import com.hnust.pojo.Course;
import com.hnust.pojo.User;
import org.apache.ibatis.annotations.Param;
import org.springframework.web.multipart.MultipartFile;

public interface CourseService {

    public paginationDTO queryAllCourse(Integer curPage, Integer pageSize);
    public int addCourse(Course course);
    public int updateCourse(Course course);
    public int deleteCourseById(int id);
    public int queryCourseCount();
    public Course queryCourseById(int id);
    public int queryCourseCountByName(@Param(value = "name")String name);
    public paginationDTO queryCourseByName(String name,Integer curPage, Integer pageSize);
    public boolean add(Course course, MultipartFile file);
    public int insertSelective(Course course);
    public int updateByIdSelective(Course course);
    public boolean update(Course course, MultipartFile file);
}
