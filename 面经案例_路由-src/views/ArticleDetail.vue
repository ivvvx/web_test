<template>
  <div class="article-detail-page">
    <nav class="nav"> <span @click="$router.back()" class="back">&lt;</span> 面经详情</nav>
    <!-- 使用v-if确保在数据加载完成后再渲染 -->
    <div v-if="article">
      <header class="header">
        <h1>{{ article.stem }}</h1>
        <p>{{ article.createdAt }} | {{ article.views }} 浏览量 | {{ article.likeCount }} 点赞数</p>
        <p>
          <img :src="article.creatorAvatar" alt="用户头像"> 
          <span>{{ article.creatorName }}</span> 
        </p>
      </header>
      <main class="body">  
        {{ article.content }}
      </main>
    </div>
    <!-- 数据加载时显示提示 -->
    <div v-else class="loading">加载中...</div>
  </div>
</template>

<script>
import axios from 'axios'
export default {
  name: 'ArticleDetailPage',
  data () {
    return {
      article: null
    }
  },
  // 创建延时函数
  methods: {
    delay (ms) {
    return new Promise(resolve => setTimeout(resolve, ms))
  },
  },
  
  async created () {
    try {
      // 先显示加载状态
      console.log('开始加载文章数据...')
      
      // 获取路由参数中的id
      const id = this.$route.params.id
      
      // 模拟网络延迟，延迟1.5秒后再请求数据
      await this.delay(1000)
      
      // 获取整个data.json文件
      const res = await axios.get('http://127.0.0.1:8081/data.json')
      
      // 根据id过滤出对应的文章
      const articleData = res.data.find(item => item.id === id)
      
      // 如果找到文章，就赋值给data中的article
      if (articleData) {
        this.article = articleData
        console.log('文章数据加载完成')
      } else {
        console.error('未找到对应的文章')
      }
    } catch (error) {
      console.error('获取文章详情失败:', error)
    }
  }
};
</script>

<style lang="less" scoped>
.article-detail-page {
  .nav {
    height: 44px;
    border-bottom: 1px solid #e4e4e4;
    line-height: 44px;
    text-align: center;
    .back {
      font-size: 18px;
      color: #666;
      position: absolute;
      left: 10px;
      top: 0;
      transform: scale(1, 1.5);
    }
  }
  .header {
     padding: 0 15px;
     p {
       color: #999;
       font-size: 12px;
       display: flex;
       align-items: center;
     }
     img {
       width: 40px;
       height: 40px;
       border-radius: 50%;
       overflow: hidden;
     }
  }
  .body {
     padding: 0 15px;
  }
  .loading {
    text-align: center;
    padding: 80px 0;
    color: #666;
    font-size: 16px;
    font-weight: 500;
    
    /* 添加加载动画 */
    position: relative;
    
    &::after {
      content: '';
      display: inline-block;
      width: 20px;
      height: 20px;
      margin-left: 10px;
      border: 2px solid #f3f3f3;
      border-top: 2px solid #409eff;
      border-radius: 50%;
      animation: spin 1s linear infinite;
    }
  }
  
  @keyframes spin {
    0% { transform: rotate(0deg); }
    100% { transform: rotate(360deg); }
  }
}
</style>