<template>
  <section class="projects" aria-labelledby="projects-heading">
    <header>
      <p class="projects__eyebrow">作品集</p>
      <h2 id="projects-heading">Projects & Case Studies</h2>
      <p class="projects__intro">
        以下项目涵盖了数据可视化、全栈开发以及设计系统落地等不同方向，均可访问在线 Demo 与代码仓库。
      </p>
    </header>

    <div class="projects__grid">
      <article v-for="project in projects" :key="project.title" class="project-card">
        <figure class="project-card__media">
          <img
            :src="project.image"
            :alt="project.title + ' 截图占位图'"
            loading="lazy"
          />
        </figure>
        <div class="project-card__body">
          <h3>{{ project.title }}</h3>
          <p>{{ project.description }}</p>
          <ul class="project-card__tags">
            <li v-for="tag in project.tech" :key="tag">{{ tag }}</li>
          </ul>
        </div>
        <div class="project-card__links">
          <a :href="project.demo" target="_blank" rel="noopener" aria-label="查看 Demo">
            <i class="fas fa-external-link-alt" aria-hidden="true"></i> Demo
          </a>
          <a :href="project.repo" target="_blank" rel="noopener" aria-label="查看 GitHub">
            <i class="fab fa-github" aria-hidden="true"></i> GitHub
          </a>
        </div>
      </article>
    </div>
  </section>
</template>

<script>
const imagePlaceholder = require('@/assets/profile-placeholder.svg')

export default {
  name: 'ProjectsView',
  data () {
    return {
      projects: [
        {
          title: 'Adaptive Learning Dashboard',
          description:
            '为在线教育平台打造的数据仪表盘，支持实时课程追踪、学生状态预测与可视化洞察。',
          tech: ['Vue 2', 'D3.js', 'Node.js'],
          demo: 'https://example.com/demo-1',
          repo: 'https://github.com/username/project-1',
          image: imagePlaceholder
        },
        {
          title: 'Design System Starter Kit',
          description:
            '封装响应式组件与主题系统的前端脚手架，帮助团队快速搭建品牌一致的界面体验。',
          tech: ['Vue', 'Storybook', 'Sass'],
          demo: 'https://example.com/demo-2',
          repo: 'https://github.com/username/project-2',
          image: imagePlaceholder
        },
        {
          title: 'Campus Community App',
          description:
            '面向高校的社区应用，提供活动报名、实时公告与聊天微服务，日活跃用户 3K+。',
          tech: ['Vue', 'Firebase', 'Tailwind'],
          demo: 'https://example.com/demo-3',
          repo: 'https://github.com/username/project-3',
          image: imagePlaceholder
        }
      ]
    }
  }
}
</script>

<style scoped>
.projects {
  display: flex;
  flex-direction: column;
  gap: 2rem;
}

.projects__eyebrow {
  text-transform: uppercase;
  color: #6b7280;
  letter-spacing: 0.18em;
}

.projects__intro {
  max-width: 680px;
  color: #4b5563;
}

.projects__grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
  gap: 1.5rem;
}

.project-card {
  background: #fff;
  border-radius: 24px;
  overflow: hidden;
  display: flex;
  flex-direction: column;
  box-shadow: 0 20px 45px rgba(15, 23, 42, 0.1);
  transition: transform 0.3s ease, box-shadow 0.3s ease;
}

.project-card:hover {
  transform: translateY(-6px);
  box-shadow: 0 30px 60px rgba(37, 99, 235, 0.2);
}

.project-card__media img {
  width: 100%;
  height: 180px;
  object-fit: cover;
}

.project-card__body {
  padding: 1.5rem;
  flex: 1;
  display: flex;
  flex-direction: column;
  gap: 0.75rem;
}

.project-card__tags {
  list-style: none;
  padding: 0;
  margin: 0;
  display: flex;
  gap: 0.5rem;
  flex-wrap: wrap;
}

.project-card__tags li {
  padding: 0.25rem 0.75rem;
  border-radius: 999px;
  background-color: rgba(37, 99, 235, 0.1);
  color: #1d4ed8;
  font-size: 0.85rem;
}

.project-card__links {
  display: flex;
  justify-content: space-between;
  padding: 1.25rem 1.5rem;
  border-top: 1px solid rgba(15, 23, 42, 0.08);
}

.project-card__links a {
  text-decoration: none;
  font-weight: 600;
  color: #1d4ed8;
  display: inline-flex;
  gap: 0.35rem;
  align-items: center;
}

@media (max-width: 640px) {
  .project-card__links {
    flex-direction: column;
    gap: 0.75rem;
  }
}
</style>
