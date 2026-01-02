<template>
  <section class="about" aria-labelledby="about-heading">
    <header>
      <p class="about__eyebrow">关于我</p>
      <h2 id="about-heading">John Doe</h2>
      <p class="about__intro">
        作为一名即将毕业的计算机科学学生，我专注于以用户为中心的前端工程、可访问性与跨端一致性。
        我喜欢探索前沿技术，并通过数据驱动的方法持续优化产品体验。
      </p>
    </header>

    <div class="about__details">
      <article class="about__card" aria-label="个人信息">
        <h3>个人信息</h3>
        <ul>
          <li>
            <i class="fas fa-user" aria-hidden="true"></i>
            <span>姓名：</span>John Doe
          </li>
          <li>
            <i class="fas fa-envelope" aria-hidden="true"></i>
            <span>邮箱：</span>
            <a href="mailto:john.doe@email.com">john.doe@email.com</a>
          </li>
          <li>
            <i class="fas fa-phone" aria-hidden="true"></i>
            <span>电话：</span>
            <a href="tel:+1234567890">+1 (234) 567-890</a>
          </li>
          <li>
            <i class="fas fa-location-dot" aria-hidden="true"></i>
            <span>所在地：</span>Seattle, WA
          </li>
        </ul>
      </article>

      <article class="about__card" aria-label="职业目标">
        <h3>职业目标</h3>
        <p>
          希望加入一个注重设计、质量与协作的团队，参与构建影响力十足的 Web 应用。
          我乐于承担跨职能沟通角色，将复杂需求转化为可落地的技术方案。
        </p>
        <p>
          兴趣领域包含可视化、设计系统、性能优化与可持续前端架构。
        </p>
      </article>
    </div>
  </section>
</template>

<script>
export default {
  name: 'AboutView'
}
</script>

<style scoped>
.about {
  display: flex;
  flex-direction: column;
  gap: 2.5rem;
}

.about__eyebrow {
  text-transform: uppercase;
  letter-spacing: 0.15em;
  color: #6b7280;
}

.about__intro {
  max-width: 680px;
  color: #4b5563;
  font-size: 1.05rem;
}

.about__details {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
  gap: 1.5rem;
}

.about__card {
  padding: 1.75rem;
  border-radius: 24px;
  background: #fff;
  box-shadow: 0 20px 45px rgba(15, 23, 42, 0.08);
}

.about__card ul {
  list-style: none;
  padding: 0;
  margin: 1rem 0 0;
  display: flex;
  flex-direction: column;
  gap: 0.75rem;
}

.about__card li {
  display: flex;
  align-items: center;
  gap: 0.5rem;
}

.about__card i {
  color: #2563eb;
  width: 24px;
}

.about__card a {
  color: inherit;
  text-decoration: none;
  border-bottom: 1px dashed transparent;
  transition: border-color 0.2s ease;
}

.about__card a:hover {
  border-color: #2563eb;
}

@media (max-width: 640px) {
  .about__card {
    padding: 1.25rem;
  }
}
</style>
