import com.itheima.pojo.Course;
import com.itheima.pojo.School;
import com.itheima.utils.MyBatisUtils;
import org.apache.ibatis.session.SqlSession;
import org.junit.Test;

import java.util.List;

public class MybatisTest {
@Test   // <!--需求1：查询 id=2 的课程信息-->
public void findCourseById(){
    SqlSession sqlSession= MyBatisUtils.getSession();
    Course course= sqlSession.selectOne("com.itheima.mapper.CourseMapper.findCourseById",2);
    System.out.println(course);
}

@Test  // <!--需求2：查询出所有计算机学院开设的课程信息 ；list:集合-->
public void findCourseBySchool(){
   SqlSession sqlSession=MyBatisUtils.getSession();
    List<Course> list=sqlSession.selectList("com.itheima.mapper.CourseMapper.findCourseBySchool","计算机学院");
    for (Course course:list){
        System.out.println(course);
    }
        sqlSession.close();
}

@Test    // <!--需求3：将 id=4 这⻔课程的课时数修改为 32+8=40；
    public void updateCourse(){
    SqlSession sqlSession=MyBatisUtils.getSession();
    int row=sqlSession.update("com.itheima.mapper.CourseMapper.updateCourse",4);
    if (row>0)
        System.out.println("您修改成功了"+row+"行数据");
    else
        System.out.println("修改失败");
    sqlSession.commit();
    sqlSession.close();
}
    //<!--需求4：插⼊⼀条新的课程记录： names=”⼤数据存储“，hours=32，schools =1；-->
    @Test
    public void insertCourse(){
        SqlSession sqlSession=MyBatisUtils.getSession();
        int row=sqlSession.insert("com.itheima.mapper.CourseMapper.insertCourse");
        if (row>0)
            System.out.println("插入成功"+row+"行数据");
        else
            System.out.println("插入失败");
        sqlSession.commit();
        sqlSession.close();
        //<!--更新 、插入数据需要手动提交事物并回滚-->
    }

    // <!--需求5：输出所有的学院开设的课程信息。-->
    @Test
    public void findAllCourse(){
        SqlSession sqlSession=MyBatisUtils.getSession();
        Integer[] a=new Integer[]{1,2};
        List<Course>list=sqlSession.selectList("com.itheima.mapper.CourseMapper.findAllCourse",a);
        for (Course c:list){
            System.out.println(c);
        }
        sqlSession.commit();
        sqlSession.close();
    }

    @Test
    public void  findSchoolWithCourseById(){
    SqlSession sqlSession=MyBatisUtils.getSession();
    Integer[]a=new Integer[]{1,2};
    List<School>list=sqlSession.selectList("com.itheima.mapper.SchoolMapper.findSchoolWithCourseById",a);
    for(School c:list){
        System.out.println(c);
        }
       sqlSession.commit();
    sqlSession.close();
    }
}