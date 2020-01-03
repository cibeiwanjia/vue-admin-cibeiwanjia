<template>
    <div>
        <b>栏目管理</b>
       
        <el-button size="small" type="success" @click="toAddHandler">添加</el-button>
        <el-button size="small" type="danger">批量删除</el-button>

        <el-table  :data="categories">
            <el-table-column prop="id" label="编号"></el-table-column>
            <el-table-column prop="name" label="栏目名称"></el-table-column>
            <el-table-column prop="num" label="序号"></el-table-column>
            <el-table-column prop="parentId" label="父栏目"></el-table-column>
            <el-table-column fixed="right" label="操作">
                <!-- v-slot用于获取当前行数据 -->
                <template v-slot="slot">
                    <a href=""  @click.prevent="toDeleteHandler(slot.row.id)">删除</a>
                    <a href="" @click.prevent="toUpdateHandler(slot.row)">修改</a>
                </template>
            </el-table-column>
        </el-table>
        <!-- 模态框    冒号表示引用脚本-->
         <el-dialog :title="title" :visible.sync="visible" width="50%" >
         <el-form :model="form" label-width="80px">
             <el-form-item label="栏目名称">
                 <el-input v-model="form.name"/>
             </el-form-item>
             <el-form-item label="序号">
                 <el-input v-model="form.id"/>
             </el-form-item>
         </el-form>
         <span slot="footer" class="dialog-footer">
         <el-button @click="visible = false">取 消</el-button>
         <!-- @click=onclick -->
         <el-button type="primary" @click="submitHandler">确 定</el-button>
         </span>
        </el-dialog>
        <!-- /模态框 -->

    </div>
</template>
<script>
import request from '@/utils/request'
import querystring from 'querystring'
export default {
     created(){
        //在页面加载出来的时候加载数据
        this.loadData()
    },
    data() {
        return {
            title:"添加栏目信息",
            visible:false,
            categories:[],
            form:{
                type:"category"
            }
        }
    },
    methods:{
        loadData(){
            //this指向vue实例。
            let url = "http://localhost:6677/category/findAll";
            request.get(url).then((response)=>{
                //箭头函数中的this指向外部函数中的this
                this.categories = response.data;
            })
        },
        closeMethodHandler(){
            this.visible = false;
        },
        submitHandler(){
            let url = "http://localhost:6677/category/saveOrUpdate";
            //前端向后台发送请求，完成数据的保存操作
            request({
                url,
                method:"POST",
                headers:{
                    "Content-Type":"application/x-www-form-urlencoded"
                },
                data:querystring.stringify(this.form)
            }).then((response)=>{
                this.closeMethodHandler();
                this.loadData();
                this.$message({type:"success",message:response.message});
            })
        },
        toAddHandler(){
            this.visable = true;
        },
        toDeleteHandler(){
            this.$confirm('此操作将永久删除该文件, 是否继续?', '提示', {
          confirmButtonText: '确定',
          cancelButtonText: '取消',
          type: 'warning'
        }).then(() => {
          this.$message({
            type: 'success',
            message: '删除成功!'+id
          });
        })
        },
        toUpdateHandler(){
            this.title="修改员工信息";
            this.visible=true;
        }
    }
}
</script>