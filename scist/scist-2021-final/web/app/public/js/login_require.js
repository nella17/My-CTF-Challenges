fetch('/verify').then(res => res.json())
  .then(({ done }) => {
    if (!done) location.href = '/logout.html'
  })
