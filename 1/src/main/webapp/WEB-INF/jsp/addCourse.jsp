<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>

<html>
<head>
    <title>新增课程</title>
    <base href="<%=request.getContextPath()%>/"/>
    <style>
        div {list-style: none;color: #2b2b2b; }

    </style>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <!-- 引入 Bootstrap -->
    <link href="https://fastly.jsdelivr.net/npm/bootstrap@3.3.7/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body style="background: url(img/background.jpg)">
<div class="container">

    <div class="row clearfix">
        <div class="col-md-12 column">
            <div class="page-header">
                <h1>
                    <small>新增课程</small>
                </h1>
            </div>
        </div>
    </div>

    <form action="${pageContext.request.contextPath}/course/addCourse" method="post"
          enctype="multipart/form-data"
          modelAttribute="course" style="width: 30%">
        <div class="form-group">
            <label for="name">课程名称：</label>
            <input type="text" class="form-control" id="name" name="name" placeholder="课程名称">
        </div>
        <div class="form-group">
            <label for="hours"> 课程时长：</label>
            <input type="text" class="form-control" id="hours" name="hours" placeholder="课程时长">
        </div>
        <div class="form-group">
            <label for="school"> 开设学院：</label>
            <input type="text" class="form-control" id="school" name="school" placeholder="开设学院">
        </div>
       <div class="form-group">
            <label for="picture"> 课程图片：</label>
            <input type="file" class="form-control" id="picture" name="imgFile" placeholder="课程图片">
        </div>
        <input class="btn btn-primary" type="submit" value="提交"/>
    </form>


</div>
</body>
</html>
