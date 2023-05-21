package com.itheima.pojo;

import java.util.List;

public class School {
    private Integer id;
    private  String schoolname;
    private List<Course> courseList;//学校关联的课程，把课程声明进来

    @Override
    public String toString() {
        return "School{" +
                "id=" + id +
                ", schoolname='" + schoolname + '\'' +
                ", courseList=" + courseList +
                '}';
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getSchoolname() {
        return schoolname;
    }

    public void setSchoolname(String schoolname) {
        this.schoolname = schoolname;
    }

    public List<Course> getCourseList() {
        return courseList;
    }

    public void setCourseList(List<Course> courseList) {
        this.courseList = courseList;
    }
}

