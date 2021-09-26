/////////////////////////////////////////////
//                                         //
//    Copyright (C) 2021-2021 Julian Uy    //
//  https://sites.google.com/site/awertyb  //
//                                         //
//   See details of license at "LICENSE"   //
//                                         //
/////////////////////////////////////////////

#include "ncbind/ncbind.hpp"
#include "discord_rpc.h"
#include "discord_register.h"
#include "CharacterSet.h"

class DiscordRPC
{
public:
	static void Initialize(tTJSVariant applicationId, tTJSVariant handlers, tTJSVariant autoRegister, tTJSVariant optionalSteamId)
	{
		// TODO: handlers
		DiscordEventHandlers handlers_c;
		memset(&handlers_c, 0, sizeof(handlers_c));
		tjs_string applicationId_utf16 = ttstr(applicationId).c_str();
		std::string applicationId_utf8;
		TVPUtf16ToUtf8(applicationId_utf8, applicationId_utf16);
		tjs_string optionalSteamId_utf16 = ttstr(optionalSteamId).c_str();
		std::string optionalSteamId_utf8;
		TVPUtf16ToUtf8(optionalSteamId_utf8, optionalSteamId_utf16);
		Discord_Initialize(applicationId_utf8.c_str(), &handlers_c, !!(autoRegister.AsInteger()), optionalSteamId_utf8.length() > 0 ? optionalSteamId_utf8.c_str() : nullptr);
	}
	static void Shutdown(void)
	{
		Discord_Shutdown();
	}
	static void RunCallbacks(void)
	{
		Discord_RunCallbacks();
	}
#if 0
	static void UpdateConnection(void)
	{
		Discord_UpdateConnection();
	}
#endif
	static void UpdatePresence(tTJSVariant presence)
	{
		DiscordRichPresence presence_c;
		memset(&presence_c, 0, sizeof(presence_c));
		tTJSVariantClosure presence_closure = presence.AsObjectClosureNoAddRef();

#define X(name) \
	static ttstr name##_name = TJS_W(#name); \
	tTJSVariant name##_variant; \
	presence_closure.PropGet(0, name##_name.c_str(), name##_name.GetHint(), &name##_variant, nullptr); \
	tjs_string name##_utf16 = ttstr(name##_variant).c_str(); \
	std::string name##_utf8; \
	TVPUtf16ToUtf8(name##_utf8, name##_utf16); \
	presence_c.name = name##_utf8.length() > 0 ? name##_utf8.c_str() : nullptr;
#define Y(name) \
	static ttstr name##_name = TJS_W(#name); \
	tTJSVariant name##_variant; \
	presence_closure.PropGet(0, name##_name.c_str(), name##_name.GetHint(), &name##_variant, nullptr); \
	presence_c.name = name##_variant.AsInteger();

		X(state);
		X(details);
		Y(startTimestamp);
		Y(endTimestamp);
		X(largeImageKey);
		X(largeImageText);
		X(smallImageKey);
		X(smallImageText);
		X(partyId);
		Y(partySize);
		Y(partyMax);
		Y(partyPrivacy);
		X(matchSecret);
		X(joinSecret);
		X(spectateSecret);
		Y(instance);
#undef X
#undef Y
		Discord_UpdatePresence(&presence_c);
	}
	static void ClearPresence(void)
	{
		Discord_ClearPresence();
	}
	static void Respond(tTJSVariant userid, tTJSVariant reply)
	{
		tjs_string userid_utf16 = ttstr(userid).c_str();
		std::string userid_utf8;
		TVPUtf16ToUtf8(userid_utf8, userid_utf16);
		Discord_Respond(userid_utf8.c_str(), reply.AsInteger());
	}
	static void UpdateHandlers(tTJSVariant handlers)
	{
		// TODO: implement
	}
	static void Register(tTJSVariant applicationId, tTJSVariant command)
	{
		tjs_string applicationId_utf16 = ttstr(applicationId).c_str();
		std::string applicationId_utf8;
		TVPUtf16ToUtf8(applicationId_utf8, applicationId_utf16);
		tjs_string command_utf16 = ttstr(command).c_str();
		std::string command_utf8;
		TVPUtf16ToUtf8(command_utf8, command_utf16);
		Discord_Register(applicationId_utf8.c_str(), command_utf8.c_str());
	}
	static void RegisterSteamGame(tTJSVariant applicationId, tTJSVariant steamId)
	{
		tjs_string applicationId_utf16 = ttstr(applicationId).c_str();
		std::string applicationId_utf8;
		TVPUtf16ToUtf8(applicationId_utf8, applicationId_utf16);
		tjs_string steamId_utf16 = ttstr(steamId).c_str();
		std::string steamId_utf8;
		TVPUtf16ToUtf8(steamId_utf8, steamId_utf16);
		Discord_RegisterSteamGame(applicationId_utf8.c_str(), steamId_utf8.c_str());
	}
};

NCB_REGISTER_CLASS(DiscordRPC)
{
	NCB_METHOD(Initialize);
	NCB_METHOD(Shutdown);
	NCB_METHOD(RunCallbacks);
#if 0
	NCB_METHOD(UpdateConnection);
#endif
	NCB_METHOD(UpdatePresence);
	NCB_METHOD(ClearPresence);
	NCB_METHOD(Respond);
	NCB_METHOD(UpdateHandlers);
	NCB_METHOD(Register);
	NCB_METHOD(RegisterSteamGame);
};
