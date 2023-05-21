package com.hnust.mapper;

import com.hnust.pojo.Course;

import org.apache.ibatis.annotations.Param;

import java.util.List;
public interface CourseMapper {
    public List<Course> queryAllCourse(@Param(value = "curPage")int curPage,
                                       @Param(value = "pageSize")int pageSize);
    public int addCourse(Course course);
    public int updateCourse(Course course);
    public int deleteCourseById(@Param(value = "id") int id);
    public int queryCourseCount();
    public Course queryCourseById(@Param(value = "id")int id);
    public List<Course> queryCourseByName(@Param(value = "name") String name,
                                          @Param(value = "curPage")int curPage,
                                          @Param(value = "pageSize")int pageSize);
    public int queryCourseCountByName(@Param(value = "name")String name);
    public int insertSelective(Course course);
    public int updateByIdSelective(Course course);

}
