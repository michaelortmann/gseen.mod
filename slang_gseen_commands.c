#include <stddef.h>

static void slang_send_botnick()
{
  strlcpy(slang_text_buf + strlen(slang_text_buf), botname, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

static void slang_send_query()
{
  if (glob_query)
    strlcpy(slang_text_buf + strlen(slang_text_buf), glob_query, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

static void slang_send_laston()
{
  if (glob_laston)
    strlcpy(slang_text_buf + strlen(slang_text_buf), glob_laston, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

static void slang_send_otherchan()
{
  if (glob_otherchan)
    strlcpy(slang_text_buf + strlen(slang_text_buf), glob_otherchan, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

static void slang_send_othernick()
{
  if (glob_othernick)
    strlcpy(slang_text_buf + strlen(slang_text_buf), glob_othernick, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

static void slang_send_remotebot()
{
  if (glob_remotebot)
    strlcpy(slang_text_buf + strlen(slang_text_buf), glob_remotebot, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

static void slang_send_snick()
{
  if (glob_seendat)
    strlcpy(slang_text_buf + strlen(slang_text_buf), glob_seendat->nick, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

static void slang_send_shost()
{
  if (glob_seendat)
    strlcpy(slang_text_buf + strlen(slang_text_buf), glob_seendat->host, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

static void slang_send_schan()
{
  if (glob_seendat)
    strlcpy(slang_text_buf + strlen(slang_text_buf), glob_seendat->chan, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

static void slang_send_swhen()
{
  char *dur;

  if (glob_seendat) {
    dur = gseen_duration(now - glob_seendat->when);
    strlcpy(slang_text_buf + strlen(slang_text_buf), dur, sizeof(slang_text_buf) - strlen(slang_text_buf));
  }
}

static void slang_send_stime()
{
  time_t tt;
  char t[20];
  
  if (glob_seendat) {
    tt = glob_seendat->when;
    strftime(t, sizeof(t), "%d.%m.%Y %H:%M", localtime(&tt));
    strlcpy(slang_text_buf + strlen(slang_text_buf), t, sizeof(slang_text_buf) - strlen(slang_text_buf));
  }
}

static void slang_send_spent()
{
  char *dur;

  if (glob_seendat) {
    dur = gseen_duration(glob_seendat->spent);
    strlcpy(slang_text_buf + strlen(slang_text_buf), dur, sizeof(slang_text_buf) - strlen(slang_text_buf));
  }
}

static void slang_send_smsg()
{
  if (glob_seendat)
    strlcpy(slang_text_buf + strlen(slang_text_buf), glob_seendat->msg, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

static void slang_send_numresults()
{
  char buf[7];
  
  snprintf(buf, sizeof(buf), "%d", numresults);
  strlcpy(slang_text_buf + strlen(slang_text_buf), buf, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

static void slang_send_punisher()
{
  char *reason;
  ptrdiff_t len;
  
  if (glob_seendat) {
    reason = strchr(glob_seendat->msg, ' ');
    if (!reason)
      strlcpy(slang_text_buf + strlen(slang_text_buf), glob_seendat->msg, sizeof(slang_text_buf) - strlen(slang_text_buf));
    else {
      len = reason - glob_seendat->msg;
      strlcpy(slang_text_buf + strlen(slang_text_buf), glob_seendat->msg, (sizeof(slang_text_buf) < len) ? sizeof(slang_text_buf) : len);
    }
  }
}

static void slang_send_kickreason()
{
  char *reason;
  
  if (glob_seendat) {
    reason = strchr(glob_seendat->msg, ' ');
    if (reason)
      strlcpy(slang_text_buf + strlen(slang_text_buf), reason, sizeof(slang_text_buf) - strlen(slang_text_buf));
  }
}

static void slang_send_rnick()
{
  if (glob_seenrequest) {
    Assert(glob_seenrequest->by);
    Assert(glob_seenrequest->by->who);
    strlcpy(slang_text_buf + strlen(slang_text_buf), glob_seenrequest->by->who, sizeof(slang_text_buf) - strlen(slang_text_buf));
  }
}

static void slang_send_rchan()
{
  if (glob_seenrequest) {
    Assert(glob_seenrequest->by);
    Assert(glob_seenrequest->by->chan);
    strlcpy(slang_text_buf + strlen(slang_text_buf), glob_seenrequest->by->chan, sizeof(slang_text_buf) - strlen(slang_text_buf));
  }
}

static void slang_send_rhost()
{
  if (glob_seenrequest) {
    Assert(glob_seenrequest->by);
    Assert(glob_seenrequest->by->host);
    strlcpy(slang_text_buf + strlen(slang_text_buf), glob_seenrequest->by->host, sizeof(slang_text_buf) - strlen(slang_text_buf));
  }
}

static void slang_send_rtime()
{
  time_t tt;
  char t[20];
  
  if (glob_seenrequest) {
    Assert(glob_seenrequest->by);
    tt = glob_seenrequest->by->when;
    strftime(t, sizeof(t), "%d.%m.%Y %H:%M", localtime(&tt));
    strlcpy(slang_text_buf + strlen(slang_text_buf), t, sizeof(slang_text_buf) - strlen(slang_text_buf));
  }
}

static void slang_send_rwhen()
{
  if (glob_seenrequest) {
    Assert(glob_seenrequest->by);
    strlcpy(slang_text_buf + strlen(slang_text_buf), gseen_duration(now - glob_seenrequest->by->when), sizeof(slang_text_buf) - strlen(slang_text_buf));
  }
}

static void slang_send_requests()
{
  char buf[7];
  
  snprintf(buf, sizeof(buf), "%d", glob_seenrequests);
  strlcpy(slang_text_buf + strlen(slang_text_buf), buf, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

static void slang_send_totalnicks()
{
  char buf[7];
  
  snprintf(buf, sizeof(buf), "%d", glob_totalnicks);
  strlcpy(slang_text_buf + strlen(slang_text_buf), buf, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

static void slang_send_totalbytes()
{
  char buf[20];
  
  snprintf(buf, sizeof(buf), "%d", glob_totalbytes);
  strlcpy(slang_text_buf + strlen(slang_text_buf), buf, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

static void slang_send_nick()
{
  if (glob_nick)
    strlcpy(slang_text_buf + strlen(slang_text_buf), glob_nick, sizeof(slang_text_buf) - strlen(slang_text_buf));
}

struct slang_text_commands slang_text_gseen_command_table[] =
{
  {"botnick", slang_send_botnick},
  {"query", slang_send_query},
  {"laston", slang_send_laston},
  {"otherchan", slang_send_otherchan},
  {"othernick", slang_send_othernick},
  {"remotebot", slang_send_remotebot},
  {"snick", slang_send_snick},
  {"swhen", slang_send_swhen},
  {"stime", slang_send_stime},
  {"shost", slang_send_shost},
  {"schan", slang_send_schan},
  {"spent", slang_send_spent},
  {"smsg", slang_send_smsg},
  {"numresults", slang_send_numresults},
  {"snick2", slang_send_smsg},
  {"bnbot", slang_send_smsg},
  {"punisher", slang_send_punisher},
  {"kickreason", slang_send_kickreason},
  {"rnick", slang_send_rnick},
  {"rchan", slang_send_rchan},
  {"rhost", slang_send_rhost},
  {"rtime", slang_send_rtime},
  {"rwhen", slang_send_rwhen},
  {"requests", slang_send_requests},
  {"totalnicks", slang_send_totalnicks},
  {"totalbytes", slang_send_totalbytes},
  {"nick", slang_send_nick},
  {0, 0}
};
