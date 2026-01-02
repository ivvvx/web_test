<template>
  <header class="hero" aria-label="个人简介与导航">
    <nav class="hero__nav" aria-label="主导航">
      <router-link class="hero__brand" to="/about" aria-label="返回关于页面">
        <span class="hero__brand-initials">JD</span>
        <span class="hero__brand-text">John Doe</span>
      </router-link>

      <ul class="hero__nav-list">
        <li v-for="link in navLinks" :key="link.label">
          <router-link
            v-if="link.type === 'route'"
            :to="link.path"
            exact-active-class="is-active"
          >
            {{ link.label }}
          </router-link>
          <button
            v-else
            type="button"
            class="hero__anchor"
            @click="scrollToContact"
          >
            {{ link.label }}
          </button>
        </li>
      </ul>

      <div class="hero__actions">
        <button
          class="hero__theme-toggle"
          type="button"
          :aria-pressed="isDarkMode.toString()"
          aria-label="切换暗色模式"
          @click="$emit('toggle-theme')"
        >
          <i :class="[isDarkMode ? 'fas fa-moon' : 'fas fa-sun']" aria-hidden="true"></i>
        </button>
        <a
          class="hero__resume"
          href="https://example.com/resume.pdf"
          target="_blank"
          rel="noopener"
        >
          下载简历
        </a>
      </div>
    </nav>

    <section class="hero__content">
      <div class="hero__text">
        <p class="hero__eyebrow">你好，我是一名</p>
        <h1>John Doe</h1>
        <p class="hero__title">计算机科学应届毕业生</p>
        <p class="hero__bio">
          我热衷于打造可靠、包容且高性能的 Web 体验，擅长前后端协作。
          目前正寻找能够让我在用户体验与工程实践间发挥桥梁作用的全职机会。
        </p>
        <div class="hero__cta">
          <router-link to="/projects" class="btn btn--primary">查看项目</router-link>
          <a
            href="#contact"
            class="btn btn--ghost"
            aria-label="跳转至联系方式"
            @click.prevent="scrollToContact"
          >
            联系我
          </a>
        </div>
      </div>

      <figure class="hero__figure">
        <img
          class="hero__photo"
          src="@/assets/profile-placeholder.svg"
          alt="个人头像占位图"
          loading="lazy"
        />
        <figcaption class="sr-only">简历头像占位图，可替换为真实照片</figcaption>
      </figure>
    </section>
  </header>
</template>

<script>
export default {
  name: 'HeaderComponent',
  props: {
    isDarkMode: {
      type: Boolean,
      default: false
    }
  },
  data () {
    return {
      navLinks: [
        { label: '关于', path: '/about', type: 'route' },
        { label: '教育', path: '/education', type: 'route' },
        { label: '项目', path: '/projects', type: 'route' },
        { label: '技能', path: '/skills', type: 'route' },
        { label: '联系', type: 'anchor' }
      ]
    }
  },
  methods: {
    scrollToContact () {
      const contactSection = document.getElementById('contact')
      if (contactSection) {
        contactSection.scrollIntoView({ behavior: 'smooth' })
        if (typeof contactSection.focus === 'function') {
          contactSection.focus()
        }
      }
    }
  }
}
</script>

<style scoped>
.hero {
  position: relative;
  padding: 2.5rem 1.5rem 3.5rem;
  background: radial-gradient(circle at top right, rgba(79, 209, 197, 0.25), transparent),
    #ffffff;
  border-bottom: 1px solid rgba(15, 23, 42, 0.08);
}

.hero__nav {
  display: flex;
  align-items: center;
  justify-content: space-between;
  gap: 1.5rem;
  margin-bottom: 2.5rem;
}

.hero__brand {
  text-decoration: none;
  display: flex;
  align-items: center;
  gap: 0.5rem;
  font-weight: 600;
  color: inherit;
}

.hero__brand-initials {
  width: 40px;
  height: 40px;
  border-radius: 12px;
  background-color: #1d4ed8;
  color: #fff;
  display: grid;
  place-items: center;
  font-size: 1rem;
}

.hero__nav-list {
  list-style: none;
  display: flex;
  gap: 1.25rem;
  padding: 0;
  margin: 0;
}

.hero__nav-list a {
  text-decoration: none;
  color: inherit;
  font-weight: 500;
  padding-bottom: 0.2rem;
  transition: color 0.2s ease, border-bottom-color 0.2s ease;
  border-bottom: 2px solid transparent;
}

.hero__nav-list a:hover,
.hero__nav-list a.is-active {
  color: #1d4ed8;
  border-bottom-color: #1d4ed8;
}

.hero__anchor {
  background: none;
  border: none;
  font: inherit;
  color: inherit;
  padding-bottom: 0.2rem;
  border-bottom: 2px solid transparent;
  cursor: pointer;
}

.hero__anchor:hover {
  color: #1d4ed8;
  border-bottom-color: #1d4ed8;
}

.hero__actions {
  display: flex;
  align-items: center;
  gap: 0.75rem;
}

.hero__theme-toggle {
  width: 40px;
  height: 40px;
  border-radius: 12px;
  border: 1px solid rgba(15, 23, 42, 0.12);
  background: transparent;
  cursor: pointer;
  transition: background-color 0.2s ease;
}

.hero__theme-toggle:hover {
  background-color: rgba(15, 23, 42, 0.05);
}

.hero__resume {
  text-decoration: none;
  padding: 0.65rem 1.25rem;
  border-radius: 999px;
  border: 1px solid #1d4ed8;
  color: #1d4ed8;
  font-weight: 600;
  transition: background-color 0.2s ease, color 0.2s ease;
}

.hero__resume:hover {
  background-color: #1d4ed8;
  color: #fff;
}

.hero__content {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
  gap: 2rem;
  align-items: center;
}

.hero__eyebrow {
  text-transform: uppercase;
  letter-spacing: 0.2em;
  font-size: 0.85rem;
  color: #6b7280;
  margin-bottom: 0.5rem;
}

.hero__title {
  font-size: 1.25rem;
  font-weight: 500;
  color: #4b5563;
}

.hero__bio {
  max-width: 520px;
  color: #4b5563;
}

.hero__cta {
  display: flex;
  gap: 0.75rem;
  margin-top: 1.5rem;
  flex-wrap: wrap;
}

.btn {
  border-radius: 999px;
  padding: 0.75rem 1.5rem;
  border: none;
  text-decoration: none;
  font-weight: 600;
  transition: transform 0.2s ease, box-shadow 0.2s ease;
  display: inline-flex;
  align-items: center;
  gap: 0.35rem;
}

.btn--primary {
  background-color: #1d4ed8;
  color: #fff;
  box-shadow: 0 10px 25px rgba(37, 99, 235, 0.25);
}

.btn--primary:hover {
  transform: translateY(-2px);
}

.btn--ghost {
  border: 1px solid rgba(15, 23, 42, 0.18);
  color: inherit;
}

.hero__figure {
  justify-self: center;
  background: linear-gradient(145deg, rgba(59, 130, 246, 0.15), rgba(99, 102, 241, 0.1));
  padding: 1rem;
  border-radius: 32px;
}

.hero__photo {
  width: 260px;
  height: 260px;
  object-fit: cover;
  border-radius: 24px;
  display: block;
  filter: drop-shadow(0 15px 30px rgba(15, 23, 42, 0.2));
}

.sr-only {
  position: absolute;
  width: 1px;
  height: 1px;
  padding: 0;
  margin: -1px;
  overflow: hidden;
  clip: rect(0, 0, 0, 0);
  border: 0;
}

@media (max-width: 960px) {
  .hero__nav {
    flex-wrap: wrap;
  }

  .hero__nav-list {
    flex: 1 1 100%;
    justify-content: space-between;
  }

  .hero__actions {
    margin-left: auto;
  }
}

@media (max-width: 640px) {
  .hero {
    padding: 2rem 1rem 2.5rem;
  }

  .hero__nav-list {
    flex-wrap: wrap;
    gap: 0.5rem;
  }

  .hero__photo {
    width: 200px;
    height: 200px;
  }
}
</style>
