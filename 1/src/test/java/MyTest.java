import com.hnust.dto.paginationDTO;
import com.hnust.pojo.Course;
import com.hnust.service.CourseService;
import org.junit.Test;
import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import java.util.List;

public class MyTest {
    @Test
    public  void test(){
        ApplicationContext context = new ClassPathXmlApplicationContext("application-service.xml");
        CourseService courseServiceImpl = context.getBean("CourseServiceImpl", CourseService.class);
        paginationDTO paginationDTO = courseServiceImpl.queryCourseByName("", 0, 3);
        List<Course> courses = paginationDTO.getData();
        for (Course course : courses) {
            System.out.println(course);
        }
    }
    @Test
    public void test1(){
        ApplicationContext context = new ClassPathXmlApplicationContext("application-service.xml");
        CourseService courseServiceImpl = context.getBean("CourseServiceImpl", CourseService.class);
        int count = courseServiceImpl.queryCourseCountByName("");
        System.out.println(count);
    }
}
