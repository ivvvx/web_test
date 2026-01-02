<template>
  <footer class="contact" id="contact" aria-label="联系方式" tabindex="-1">
    <section>
      <h2>保持联系</h2>
      <p class="contact__subtitle">
        想了解更多？通过以下渠道找到我，或留言分享你的想法。
      </p>

      <ul class="contact__social" aria-label="社交媒体链接">
        <li v-for="item in socialLinks" :key="item.label">
          <a :href="item.href" target="_blank" rel="noopener" :aria-label="item.label">
            <i :class="item.icon" aria-hidden="true"></i>
            <span>{{ item.label }}</span>
          </a>
        </li>
      </ul>
    </section>

    <form class="contact__form" @submit.prevent="handleSubmit" novalidate>
      <label>
        <span>姓名</span>
        <input
          v-model.trim="form.name"
          type="text"
          name="name"
          autocomplete="name"
          required
        />
      </label>

      <label>
        <span>邮箱</span>
        <input
          v-model.trim="form.email"
          type="email"
          name="email"
          autocomplete="email"
          required
        />
      </label>

      <label>
        <span>留言</span>
        <textarea
          v-model.trim="form.message"
          name="message"
          rows="4"
          required
        ></textarea>
      </label>

      <button type="submit" class="contact__submit">发送</button>
    </form>
  </footer>
</template>

<script>
export default {
  name: 'ContactComponent',
  data () {
    return {
      socialLinks: [
        { label: 'LinkedIn', href: 'https://linkedin.com/in/username', icon: 'fab fa-linkedin-in' },
        { label: 'GitHub', href: 'https://github.com/username', icon: 'fab fa-github' },
        { label: 'Twitter', href: 'https://twitter.com/username', icon: 'fab fa-twitter' }
      ],
      form: {
        name: '',
        email: '',
        message: ''
      }
    }
  },
  methods: {
    handleSubmit () {
      if (!this.form.name || !this.form.email || !this.form.message) {
        window.alert('请完整填写所有字段。')
        return
      }

      if (!/.+@.+\..+/.test(this.form.email)) {
        window.alert('请输入有效的邮箱地址。')
        return
      }

      window.alert('感谢留言！我会尽快回复你。')
      this.form = { name: '', email: '', message: '' }
    }
  }
}
</script>

<style scoped>
.contact {
  padding: 3rem 1.5rem 4rem;
  background-color: rgba(15, 23, 42, 0.04);
  border-top: 1px solid rgba(15, 23, 42, 0.08);
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(260px, 1fr));
  gap: 2rem;
}

.contact h2 {
  margin-bottom: 0.5rem;
}

.contact__subtitle {
  color: #4b5563;
  max-width: 420px;
}

.contact__social {
  list-style: none;
  padding: 0;
  margin: 1.5rem 0 0;
  display: flex;
  gap: 1rem;
  flex-wrap: wrap;
}

.contact__social a {
  display: inline-flex;
  align-items: center;
  gap: 0.5rem;
  padding: 0.65rem 1rem;
  border-radius: 12px;
  border: 1px solid rgba(15, 23, 42, 0.12);
  text-decoration: none;
  color: inherit;
  transition: transform 0.2s ease, box-shadow 0.2s ease;
}

.contact__social a:hover {
  transform: translateY(-2px);
  box-shadow: 0 10px 20px rgba(15, 23, 42, 0.1);
}

.contact__form {
  display: flex;
  flex-direction: column;
  gap: 1rem;
  background: #fff;
  padding: 1.5rem;
  border-radius: 20px;
  box-shadow: 0 20px 40px rgba(15, 23, 42, 0.08);
}

.contact__form label {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  font-weight: 500;
}

.contact__form input,
.contact__form textarea {
  border-radius: 12px;
  border: 1px solid rgba(15, 23, 42, 0.15);
  padding: 0.75rem 1rem;
  font-family: inherit;
  transition: border-color 0.2s ease, box-shadow 0.2s ease;
}

.contact__form input:focus,
.contact__form textarea:focus {
  border-color: #2563eb;
  box-shadow: 0 0 0 3px rgba(37, 99, 235, 0.2);
  outline: none;
}

.contact__submit {
  margin-top: 0.5rem;
  border: none;
  border-radius: 999px;
  padding: 0.85rem;
  background: linear-gradient(135deg, #2563eb, #3b82f6);
  color: #fff;
  font-weight: 600;
  cursor: pointer;
  transition: transform 0.2s ease, box-shadow 0.2s ease;
}

.contact__submit:hover {
  transform: translateY(-2px);
  box-shadow: 0 15px 30px rgba(37, 99, 235, 0.35);
}

@media (max-width: 640px) {
  .contact {
    padding: 2.5rem 1rem 3rem;
  }

  .contact__form {
    padding: 1.25rem;
  }
}
</style>
