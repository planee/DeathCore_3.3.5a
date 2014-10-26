#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "Chat.h"
#include "Common.h"
#include "Language.h"


uint32 aurasVip[] = { 79063, 79102, 79058, 85768, 79061, 79107, 79105, 26035}; // Buff Vips

class vipcommands : public CommandScript
{
public:
    vipcommands() : CommandScript("vipcommands") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand vipCommandTable[] =

        { 
	    {"Buff", SEC_VIP, true, &HandleVipBuffCommand, "", NULL},
		{ "Shop",	    SEC_VIP,     true, &HandleVipMallCommand,         "", NULL },
        { "Mudar-Raça",    SEC_VIP,  false, &HandleChangeRaceCommand,             "", NULL },
	    { "Mudar-Facção",	SEC_VIP,  false, &HandleChangeFactionCommand,		"", NULL },
	    { "Mudar-Visual",	SEC_VIP,  false, &HandleCustomizeCommand,		"", NULL },
 
            { NULL,             0,                     false, NULL,                                           "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "Vip",	    SEC_VIP,   true, NULL,      "",  vipCommandTable},
	       { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }



		static bool HandleVipBuffCommand(ChatHandler * handler, const char * args)
    {
        Player * pl = handler->GetSession()->GetPlayer();
                if(pl->InArena())
                {
                        pl->GetSession()->SendNotification("Você não pode usar este comando em arena!");
                        return false;
                }
       
                pl->RemoveAurasByType(SPELL_AURA_MOUNTED);
                for(int i = 0; i < 40; i++)
                    pl->AddAura(aurasVip[i], pl);
                handler->PSendSysMessage("|cffFFFFFF[|cffFFA500Buff Vip|cffFFFFFF] |cffFF0000Você está quase imortal!");
                return true;
 
    }

static bool HandlevipCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();

            me->Say("Comandos V.I.P?", LANG_UNIVERSAL);
            return true;
    }

static bool HandleChangeRaceCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
		handler->PSendSysMessage("Relogue para mudar sua raça.");
        return true;
    }

static bool HandleChangeFactionCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
		handler->PSendSysMessage("Relogue para mudar sua facção.");
        return true;
    }


static bool HandleCustomizeCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
		handler->PSendSysMessage("Relogue para mudar o seu visual.");
        return true;
    }
	
	static bool HandleVipMallCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();

        if (me->IsInCombat())
        {
            handler->SendSysMessage(LANG_YOU_IN_COMBAT);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // stop flight if need
        if (me->IsInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        // save only in non-flight case
        else
            me->SaveRecallPosition();

		me->TeleportTo(1, 4847.365234f, -2811.368408f, 1444.530029f, 6.261538f); // MapId, X, Y, Z, O
                return true;
    }

};

void AddSC_vipcommands()
{
    new vipcommands();
}
