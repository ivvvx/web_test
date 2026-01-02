<template>
  <section class="education" aria-labelledby="education-heading">
    <header>
      <p class="education__eyebrow">教育经历</p>
      <h2 id="education-heading">Academic Journey</h2>
      <p class="education__intro">
        在校期间，我主修计算机科学并积极参与研究、社团及实习项目，将理论与实践紧密结合。
      </p>
    </header>

    <ul class="education__timeline">
      <li
        v-for="(item, index) in education"
        :key="item.school"
        class="education__card"
      >
        <div class="education__summary">
          <div>
            <h3>{{ item.school }}</h3>
            <p>{{ item.degree }} · {{ item.major }}</p>
            <p class="education__meta">
              {{ item.period }} · GPA {{ item.gpa }}
            </p>
          </div>
          <button
            class="education__toggle"
            type="button"
            :aria-expanded="expandedIndex === index"
            @click="toggleDetails(index)"
          >
            {{ expandedIndex === index ? '收起详情' : '展开详情' }}
            <i class="fas" :class="expandedIndex === index ? 'fa-chevron-up' : 'fa-chevron-down'"></i>
          </button>
        </div>

        <transition name="accordion">
          <div
            v-if="expandedIndex === index"
            class="education__details"
          >
            <h4>亮点课程 / 成就</h4>
            <ul>
              <li v-for="achievement in item.achievements" :key="achievement">
                {{ achievement }}
              </li>
            </ul>
          </div>
        </transition>
      </li>
    </ul>
  </section>
</template>

<script>
export default {
  name: 'EducationView',
  data () {
    return {
      expandedIndex: 0,
      education: [
        {
          school: 'University of Example',
          degree: 'Bachelor of Science',
          major: 'Computer Science',
          period: '2019 - 2023',
          gpa: '3.85 / 4.00',
          achievements: [
            '课程：高级算法、分布式系统、机器学习',
            '发表一篇关于可解释 AI 的本科论文',
            '担任学生开发者俱乐部负责人'
          ]
        },
        {
          school: 'Example College',
          degree: 'Associate Degree',
          major: 'Mathematics & CS Foundation',
          period: '2017 - 2019',
          gpa: '3.9 / 4.00',
          achievements: [
            '创建校园 Hackathon 并吸引 150+ 名学生参与',
            '辅导离散数学与数据结构课程',
            '荣获院长奖学金'
          ]
        }
      ]
    }
  },
  methods: {
    toggleDetails (index) {
      this.expandedIndex = this.expandedIndex === index ? null : index
    }
  }
}
</script>

<style scoped>
.education {
  display: flex;
  flex-direction: column;
  gap: 2.5rem;
}

.education__eyebrow {
  text-transform: uppercase;
  letter-spacing: 0.2em;
  color: #6b7280;
}

.education__intro {
  max-width: 640px;
  color: #4b5563;
}

.education__timeline {
  list-style: none;
  margin: 0;
  padding: 0;
  display: flex;
  flex-direction: column;
  gap: 1.25rem;
}

.education__card {
  background: #fff;
  border-radius: 24px;
  padding: 1.75rem;
  box-shadow: 0 25px 50px rgba(15, 23, 42, 0.08);
  border-left: 4px solid #2563eb;
}

.education__summary {
  display: flex;
  justify-content: space-between;
  align-items: center;
  gap: 1rem;
  flex-wrap: wrap;
}

.education__meta {
  color: #6b7280;
  font-size: 0.95rem;
}

.education__toggle {
  border: none;
  background: rgba(37, 99, 235, 0.08);
  color: #1d4ed8;
  padding: 0.5rem 1rem;
  border-radius: 999px;
  display: inline-flex;
  align-items: center;
  gap: 0.35rem;
  cursor: pointer;
  font-weight: 600;
}

.education__details {
  margin-top: 1rem;
  padding-top: 1rem;
  border-top: 1px solid rgba(15, 23, 42, 0.08);
}

.education__details ul {
  padding-left: 1.25rem;
  color: #374151;
}

.accordion-enter-active,
.accordion-leave-active {
  transition: all 0.3s ease;
}

.accordion-enter,
.accordion-leave-to {
  opacity: 0;
  transform: translateY(-10px);
}

@media (max-width: 640px) {
  .education__card {
    padding: 1.25rem;
  }
}
</style>
