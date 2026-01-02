<template>
  <div :class="['app-shell', { 'app-shell--dark': isDarkMode }]">
    <HeaderComponent
      class="app-shell__header"
      :is-dark-mode="isDarkMode"
      @toggle-theme="toggleTheme"
    />
    <main class="page-content" aria-live="polite">
      <transition name="fade" mode="out-in">
        <router-view />
      </transition>
    </main>
    <ContactComponent class="app-shell__footer" />
  </div>
</template>

<script>
import HeaderComponent from './components/Header.vue'
import ContactComponent from './components/Contact.vue'

export default {
  name: 'App',
  components: {
    HeaderComponent,
    ContactComponent
  },
  data () {
    return {
      isDarkMode: false
    }
  },
  created () {
    this.initializeTheme()
  },
  methods: {
    initializeTheme () {
      const storedPreference = window.localStorage.getItem('preferred-theme')
      this.isDarkMode = storedPreference === 'dark'
      this.syncBodyClass()
    },
    toggleTheme () {
      this.isDarkMode = !this.isDarkMode
      window.localStorage.setItem(
        'preferred-theme',
        this.isDarkMode ? 'dark' : 'light'
      )
      this.syncBodyClass()
    },
    syncBodyClass () {
      document.body.classList.toggle('theme-dark', this.isDarkMode)
    }
  }
}
</script>

<style>
:root {
  font-family: 'Inter', 'Roboto', 'Segoe UI', system-ui, -apple-system, sans-serif;
  color: #1f2933;
  background-color: #f9fafb;
  line-height: 1.6;
}

*,
*::before,
*::after {
  box-sizing: border-box;
}

body {
  margin: 0;
  background-color: #f9fafb;
  transition: background-color 0.3s ease, color 0.3s ease;
}

body.theme-dark {
  background-color: #111827;
  color: #f3f4f6;
}

.app-shell {
  min-height: 100vh;
  display: flex;
  flex-direction: column;
  background: linear-gradient(180deg, rgba(15, 23, 42, 0.03), transparent);
}

.app-shell--dark {
  background: linear-gradient(180deg, rgba(15, 23, 42, 0.25), transparent);
}

.page-content {
  flex: 1;
  padding: 2.5rem 1.5rem 4rem;
  max-width: 1100px;
  width: 100%;
  margin: 0 auto;
}

.app-shell__header,
.app-shell__footer {
  width: 100%;
}

.fade-enter-active,
.fade-leave-active {
  transition: opacity 0.3s ease;
}

.fade-enter,
.fade-leave-to {
  opacity: 0;
}

@media (max-width: 768px) {
  .page-content {
    padding: 2rem 1rem 3rem;
  }
}
</style>
