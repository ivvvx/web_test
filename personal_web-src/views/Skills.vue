<template>
  <section class="skills" aria-labelledby="skills-heading">
    <header>
      <p class="skills__eyebrow">技能矩阵</p>
      <h2 id="skills-heading">Technical Toolkit</h2>
      <p class="skills__intro">
        在课程、实习与个人项目中积累了扎实的工程能力，并持续学习新的范式与工具。
      </p>
    </header>

    <div class="skills__grid">
      <article
        v-for="group in skillGroups"
        :key="group.name"
        class="skill-card"
        :aria-label="group.name"
      >
        <h3>{{ group.name }}</h3>
        <ul>
          <li v-for="skill in group.items" :key="skill.label">
            <div class="skill-card__label">
              <span>{{ skill.label }}</span>
              <span>{{ skill.level }}%</span>
            </div>
            <div class="skill-card__bar" role="progressbar" :aria-valuenow="skill.level" aria-valuemin="0" aria-valuemax="100">
              <span :style="{ width: skill.level + '%' }"></span>
            </div>
          </li>
        </ul>
      </article>
    </div>
  </section>
</template>

<script>
export default {
  name: 'SkillsView',
  data () {
    return {
      skillGroups: [
        {
          name: '编程语言',
          items: [
            { label: 'JavaScript / TypeScript', level: 90 },
            { label: 'Python', level: 80 },
            { label: 'Go', level: 60 }
          ]
        },
        {
          name: '框架与工具',
          items: [
            { label: 'Vue 2 / Vue 3', level: 85 },
            { label: 'Node.js & Express', level: 75 },
            { label: 'Docker & CI/CD', level: 65 }
          ]
        },
        {
          name: '软技能',
          items: [
            { label: '跨团队协作', level: 85 },
            { label: '产品洞察', level: 78 },
            { label: '技术写作', level: 72 }
          ]
        }
      ]
    }
  }
}
</script>

<style scoped>
.skills {
  display: flex;
  flex-direction: column;
  gap: 2rem;
}

.skills__eyebrow {
  text-transform: uppercase;
  color: #6b7280;
  letter-spacing: 0.16em;
}

.skills__intro {
  max-width: 640px;
  color: #4b5563;
}

.skills__grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(260px, 1fr));
  gap: 1.5rem;
}

.skill-card {
  background: #fff;
  border-radius: 24px;
  padding: 1.5rem;
  box-shadow: 0 20px 45px rgba(15, 23, 42, 0.08);
}

.skill-card ul {
  list-style: none;
  padding: 0;
  margin: 1rem 0 0;
  display: flex;
  flex-direction: column;
  gap: 1rem;
}

.skill-card__label {
  display: flex;
  justify-content: space-between;
  font-weight: 600;
}

.skill-card__bar {
  width: 100%;
  height: 8px;
  border-radius: 999px;
  background: rgba(15, 23, 42, 0.08);
  margin-top: 0.35rem;
  overflow: hidden;
}

.skill-card__bar span {
  display: block;
  height: 100%;
  border-radius: 999px;
  background: linear-gradient(135deg, #2563eb, #3b82f6);
  transition: width 0.4s ease;
}

@media (max-width: 640px) {
  .skill-card {
    padding: 1.25rem;
  }
}
</style>
