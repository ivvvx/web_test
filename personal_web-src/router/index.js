import Vue from 'vue'
import VueRouter from 'vue-router'

Vue.use(VueRouter)

const routes = [
  {
    path: '/',
    redirect: '/about'
  },
  {
    path: '/about',
    name: 'About',
    component: () => import(/* webpackChunkName: "about" */ '../views/About.vue')
  },
  {
    path: '/education',
    name: 'Education',
    component: () =>
      import(/* webpackChunkName: "education" */ '../views/Education.vue')
  },
  {
    path: '/projects',
    name: 'Projects',
    component: () =>
      import(/* webpackChunkName: "projects" */ '../views/Projects.vue')
  },
  {
    path: '/skills',
    name: 'Skills',
    component: () =>
      import(/* webpackChunkName: "skills" */ '../views/Skills.vue')
  }
]

const router = new VueRouter({
  mode: 'hash',
  routes,
  scrollBehavior () {
    return { x: 0, y: 0 }
  }
})

export default router
