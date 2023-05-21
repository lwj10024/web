package com.hnust.service;

import com.hnust.dto.paginationDTO;
import com.hnust.mapper.CourseMapper;
import com.hnust.pojo.Course;
import com.hnust.pojo.User;
import com.hnust.util.Constants;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.UUID;

@Service
public class CourseServiceImpl implements CourseService{
    @Autowired
    private CourseMapper courseMapper;

    public void setCourseMapper(CourseMapper courseMapper) {
        this.courseMapper = courseMapper;
    }

    @Override
    public int addCourse(Course course) {
        return courseMapper.addCourse(course);
    }

    @Override
    public int updateCourse(Course course) {
        return courseMapper.updateCourse(course);
    }

    @Override
    public int deleteCourseById(int id) {
        return courseMapper.deleteCourseById(id);
    }

    public int queryCourseCount(){
        return courseMapper.queryCourseCount();
    }

    @Override
    public paginationDTO queryAllCourse(Integer curPage, Integer pageSize) {
        paginationDTO<Object> paginationDTO = new paginationDTO<>();
        Integer totalPage;
        Integer totalCount = courseMapper.queryCourseCount();
        if(totalCount % pageSize == 0){
            totalPage = totalCount / pageSize;
        }else {
            totalPage = totalCount / pageSize + 1;
        }
        if (curPage < 1){
            curPage = 1;
        }
        if (curPage > totalPage){
            curPage = totalPage;
        }

        paginationDTO.setPagination(totalPage,curPage);
        Integer offset = pageSize * (curPage - 1);

        List<Course> course = courseMapper.queryAllCourse(offset, pageSize);
        paginationDTO.setData(course);

        return paginationDTO;
    }

    /**
     * 查找指定 key 的 user 对象
     * @param id
     * @return
     */
    @Override
    public Course queryCourseById(int id) {
        return courseMapper.queryCourseById(id);
    }

    @Override
    public int queryCourseCountByName(String name) {
        return courseMapper.queryCourseCountByName(name);
    }

    @Override
    public paginationDTO queryCourseByName(String name,Integer curPage, Integer pageSize) {
        paginationDTO<Object> paginationDTO = new paginationDTO<>();
        Integer totalPage;
        Integer totalCount = courseMapper.queryCourseCountByName(name);
        if (totalCount.equals(0)) {
            return paginationDTO;
        }
        if(totalCount % pageSize == 0){
            totalPage = totalCount / pageSize;
        }else {
            totalPage = totalCount / pageSize + 1;
        }
        if (curPage < 1){
            curPage = 1;
        }
        if (curPage > totalPage){
            curPage = totalPage;
        }

        paginationDTO.setPagination(totalPage,curPage);
        Integer offset = pageSize * (curPage - 1);

        List<Course> course = courseMapper.queryCourseByName(name,offset,pageSize);
        paginationDTO.setData(course);

        return paginationDTO;

    }

    /**
     * 用户注册，记录用户信息并处理上传的图片
     * @param course
     * @param file
     * @return
     */
    public boolean add(Course course, MultipartFile file){
        if (file != null){
            // 生成图片存储的名称，UUID 避免相同图片名冲突
            String originalFileName = file.getOriginalFilename(); // 原始文件名
            String suffix = originalFileName.substring(originalFileName.lastIndexOf(".")); // 图片后缀
            String fileName = UUID.randomUUID().toString() + suffix;
            String filePath = Constants.IMG_PATH + fileName;
            File saveFile = new File(filePath);
            try {
                // 将上传的文件保存到服务器文件系统
                file.transferTo(saveFile);
                // 记录服务器文件系统图片名称
                course.setPicture(fileName);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        // 持久化 user
        return courseMapper.insertSelective(course) > 0;
    }

    public boolean update(Course course, MultipartFile file){
        if (file != null){
            // 生成图片存储的名称，UUID 避免相同图片名冲突
            String originalFileName = file.getOriginalFilename(); // 原始文件名
            String suffix = originalFileName.substring(originalFileName.lastIndexOf(".")); // 图片后缀
            String fileName = UUID.randomUUID().toString() + suffix;
            String filePath = Constants.IMG_PATH + fileName;
            File saveFile = new File(filePath);
            try {
                // 将上传的文件保存到服务器文件系统
                file.transferTo(saveFile);
                // 记录服务器文件系统图片名称
                course.setPicture(fileName);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        // 持久化 user
        return courseMapper.updateByIdSelective(course)> 0;
    }

    public int insertSelective(Course course){
        return courseMapper.insertSelective(course);
    }
    public int updateByIdSelective(Course course){
        return courseMapper.updateByIdSelective(course);
    }

}
