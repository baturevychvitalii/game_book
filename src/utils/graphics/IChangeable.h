#ifndef __INTERFACE_ICHANGEABLE__
#define __INTERFACE_ICHANGEABLE__

/**
This interface allows not to redraw windows that often.
*/
class IChangeable
{
    private:
        // will also be notified about change
        IChangeable * parent;
        bool up_to_date;
        
        virtual void ApplyChange() = 0;
    public:
		/**
		creates instance of class IChangeable with a provided parent
		@param parent instance of class IChangeable, which will be notified when something
		interesting changed in this window
		*/
        IChangeable(IChangeable * parent)
            :   parent(parent), 
                up_to_date(false)
        {
        }

        virtual ~IChangeable() = default;

		/**
		applyes changes to this window if it isn't up to date
		*/
        void Commit()
        {
            if (!up_to_date)
			{
				ApplyChange();
				up_to_date = true;
			}
        }

		/**
		only sends notification to a parent
		*/
		void NotifyParent()
		{
			if (parent)
				parent->NotifyChange();
		}

		/**
		if IChangeable item was changed in the way it affects it's parent
		it'll notify the parent so it'll make appropriate reactions to this
		change in It's overriden ApplyChange() function
		*/
        void NotifyChange()
        {
            up_to_date = false;
			NotifyParent();
        }

		/**
		Tells if window is up to date or it shall be updateds
		*/
        bool UpToDate() const
        {
            return up_to_date;
        }

		/**
		sets parent to a new one
		*/
        void SetParent(IChangeable * new_parent)
        {
            parent = new_parent;
        }

		/**
		tells if this window has a parent
		*/
		bool HasParent() const
		{
			return parent != nullptr;
		}
};


#endif
