<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<head >
    <title>书籍列表</title>
    <base href="<%=request.getContextPath()%>/"/>
    <style>
        li {list-style: none; background: #c0a16b}
    </style>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">


    <!-- 引入 Bootstrap -->
    <link href="https://fastly.jsdelivr.net/npm/bootstrap@3.3.7/dist/css/bootstrap.min.css" rel="stylesheet">

</head>
<body background="addCourse.jsp">

<div class="container">

    <div class="row clearfix">
        <div class="col-md-12 column">
            <div class="page-header">
                <h1>
                    <small>课程列表 —— 显示所有课程</small>
                </h1>

            </div>
        </div>
    </div>

    <div class="row">
        <div class="col-md-9 column">
            <a class="btn btn-primary" href="${pageContext.request.contextPath}/course/toAddCourse">新增</a>
            <a class="btn btn-primary" href="${pageContext.request.contextPath}/course/allCourse">显示所有课程</a>
            <span style="color: red">${error}</span>
        </div>
        <div class="col-md-3 column">
            <form action="${pageContext.request.contextPath}/course/queryCourse" method="post" >
                <div class="input-group">
                    <input type="text" name="name" class="form-control" placeholder="请输入要查找的课程">
                    <span class="input-group-btn">
                        <button class="btn btn-primary" type="submit">查询</button>
                        </span>
                </div><!-- /input-group -->
            </form>
        </div>
    </div>

    <div class="row clearfix">
        <div class="col-md-12 column">
            <table class="table table-hover table-striped">
                <thead>
                <tr>
                    <th>课程编号</th>
                    <th>课程名字</th>
                    <th>课程时长</th>
                    <th>开设学院</th>
                    <th>课程图片</th>
                    <th>操作</th>
                </tr>
                </thead>
                <tbody>
                <c:forEach var="course" items="${list.data}">
                    <tr>
                        <td>${course.getId()}</td>
                        <td>${course.getName()}</td>
                        <td>${course.getHours()}</td>
                        <td>${course.getSchool()}</td>
                        <td><img src="course/showPic/${course.getPicture()}"
                                 style="width:100px; height: 100px;"/></td>
                        <td>
                            <a href="${pageContext.request.contextPath}/course/toUpdateCourse?id=${course.getId()}">更改</a> |
                            <a href="${pageContext.request.contextPath}/course/del/${course.getId()}">删除</a>
                        </td>
                    </tr>
                </c:forEach>

                </tbody>
            </table>
        </div>
    </div>
    <nav aria-label="Page navigation">
        <ul class="pagination" style="float: right">
            <c:if test="${list.showFirstPage}">
                <li>
                    <a href="${pageContext.request.contextPath}/course/queryCourseByName?curPage=1&name=${name}" aria-label="Previous">
                        <span aria-hidden="true">首页</span>
                    </a>
                </li>
            </c:if>

            <c:if test = "${list.showPrevious}">
                <li>
                    <a href="${pageContext.request.contextPath}/course/queryCourse?curPage=${list.page -1}&name=${name}" aria-label="Previous">
                        <span aria-hidden="true">上一页</span>
                    </a>
                </li>
            </c:if>

            <c:forEach var="page" items="${list.pages}" >
                <li><a href="${pageContext.request.contextPath}/course/queryCourse?curPage=${page}&name=${name}" >${page}</a></li>
            </c:forEach>

            <c:if test = "${list.showNext}">
                <li >
                    <a href="${pageContext.request.contextPath}/course/queryCourse?curPage=${list.page + 1}&name=${name}" aria-label="Next">
                        <span aria-hidden="true">下一页</span>
                    </a>
                </li>
            </c:if>

            <c:if test = "${list.showEndPage}">
                <li>
                    <a href="${pageContext.request.contextPath}/course/queryCourse?curPage=${list.totalPage}&name=${name}" aria-label="Previous">
                        <span aria-hidden="true">尾页</span>
                    </a>
                </li>
            </c:if>

        </ul>
    </nav>
</div>
